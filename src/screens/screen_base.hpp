// screen_base.hpp
#ifndef SCREEN_BASE_HPP
#define SCREEN_BASE_HPP

#include <ftxui/component/component.hpp>  // for Renderer, Component
#include <ftxui/component/event.hpp>      // for Event

namespace screens {
    class ScreenBase {
    public:
        virtual ~ScreenBase() = default;
        virtual ftxui::Component Render() = 0;
        virtual bool HandleEvent(ftxui::Event event) = 0;
    };
}
#endif  // SCREEN_BASE_HPP
