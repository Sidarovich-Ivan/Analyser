#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"

namespace analyzer {

namespace rv = std::ranges::views;
namespace rs = std::ranges;
/**
 * @brief Анализирует список Python-файлов и извлекает метрики для всех функций и методов.
 *
 * Эта функция — центральный "конвейер" обработки:
 * 1. Принимает имена файлов.
 * 2. Для каждого файла создаёт объект `File`, который автоматически парсит его через tree-sitter
 *    и строит AST.
 * 3. Извлекает из AST все функции и методы с помощью `FunctionExtractor`.
 * 4. Объединяет все функции из всех файлов в один плоский список (`join`).
 * 5. Для каждой функции вычисляет набор метрик через переданный `metric_extractor`.
 * 6. Возвращает вектор пар: (функция, результаты её метрик).
 */
auto AnalyseFunctions(const std::vector<std::string> &files,
                      const analyzer::metric::MetricExtractor &metric_extractor) {

    std::vector<std::pair<function::Function, metric::MetricResults>> result;
    function::FunctionExtractor extractor;

    for (const auto &filename : files) {

        try {

            file::File file(filename);
            auto functions = extractor.Get(file);

            for (auto &fn : functions)
                result.emplace_back(std::move(fn), metric_extractor.Get(fn));

        } catch (const std::exception &e) {
            throw std::runtime_error(std::format("Error during file processing {}. Reason: {}", filename, e.what()));

        } catch (...) {
            throw std::runtime_error(
                std::format("Error during file processing {}. Reason: Unknown exception.", filename));
        }
    }

    return result;
}

/**
 *
 * @brief Группирует результаты анализа по классам.
 *
 * Эта функция:
 * 1. Отфильтровывает только те функции, которые являются **методами классов**
 *    (у них `class_name.has_value()` == true).
 * 2. Группирует последовательные элементы с одинаковым именем класса с помощью `chunk_by`.
 *
 * Важно:
 * - `chunk_by` работает только с **последовательными** одинаковыми элементами!
 *   Поэтому предполагается, что входной диапазон уже упорядочен по классам
 *   (например, порядок методов в AST сохраняется как в исходном файле).
 * - Если порядок нарушен, один и тот же класс может быть разбит на несколько групп.
 *
 *  Чтобы убедиться, что фильтрация работает, проверьте, что свободные функции (без class_name)
 * действительно исчезают из результата.
 */
auto SplitByClasses(const auto &analysis) {

    return analysis | std::views::filter([](const auto &pr) {
               const auto &[fn, _] = pr;
               return fn.class_name.has_value();
           }) |
           std::views::chunk_by([](const auto &curr, const auto &next) {
               const auto &[fn_curr, _] = curr;
               const auto &[fn_next, __] = next;

               return fn_curr.class_name.value() == fn_next.class_name.value();
           });
}

/**
 * @brief Группирует результаты анализа по исходным файлам.
 *
 * Эта функция:
 * - Разбивает весь список функций на группы, где каждая группа содержит
 *   только функции из одного и того же файла (`filename`).
 * - Использует `chunk_by`, поэтому **порядок функций в `analysis` должен быть по файлам**.
 */
auto SplitByFiles(const auto &analysis) {
    // clang-format off

    return analysis | 
        std::views::filter([](const auto &pr) {
            const auto &[fn, _] = pr;
            return !fn.class_name.has_value();
        }) | 
        std::views::chunk_by([](const auto &curr, const auto &next) {
             const auto &[fn_curr, _] = curr;
             const auto &[fn_next, __] = next;

             return fn_curr.filename == fn_next.filename;
        });

    // clang-format on
}

/**
 * @brief Агрегирует метрики всех функций с помощью аккумулятора.
 *
 * Эта функция:
 * - Проходит по каждому элементу результата `AnalyseFunctions`
 *   (то есть по каждой функции и её метрикам).
 * - Передаёт результаты метрик (`elem.second`) в аккумулятор через `AccumulateNextFunctionResults`.
 */
void AccumulateFunctionAnalysis(const auto &analysis, analyzer::metric_accumulator::MetricsAccumulator &accumulator) {

    for (const auto &m_res : analysis)
        accumulator.AccumulateNextFunctionResults(m_res.second);
}
}  // namespace analyzer
