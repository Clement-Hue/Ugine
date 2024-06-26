#include "pch.h"
#include "mocks.h"
#include "ugine/event/window_event.h"

class TestBaseWindow final: public ugine::window::BaseWindow {
public:
    explicit TestBaseWindow(std::unique_ptr<ugine::window::WindowImpl> window_impl,
    std::unique_ptr<ugine::ui::UI> ui = nullptr) : BaseWindow(std::move(window_impl), std::move(ui)) {}
    [[nodiscard]] std::unique_ptr<ugine::window::WindowImpl> create() const override {return std::make_unique<mocks::TestWindowImpl>();}
};

TEST(Window, EventCallback) {
    auto test_window = mocks::TestWindowImpl();
    int i = 0;
    test_window.on_event([&i](const ugine::event::Event &event) {
        ++i;
    });
    test_window.on_event([&i](const ugine::event::Event &event) {
        ++i;
    });
    test_window.test_dispatch( ugine::event::WindowQuit() );
    EXPECT_EQ(i, 2);
}

TEST(BaseWindow, CreateWindow) {
    auto test_ui = std::make_unique<mocks::TestUI>() ;
    auto test_window_impl = std::make_unique<mocks::TestWindowImpl>();
    auto* const pt_test_window_impl = test_window_impl.get();
    auto* const pt_test_ui = test_ui.get();
    const auto base_window = std::make_unique<TestBaseWindow>(
            std::move(test_window_impl), std::move(test_ui)
            );
    EXPECT_CALL(*pt_test_ui, add_impl());
    EXPECT_CALL(*pt_test_window_impl, open(testing::_));
    base_window->open();
}

TEST(Window, CloseWindow) {
    auto test_ui = std::make_unique<mocks::TestUI>() ;
    auto test_window_impl = std::make_unique<mocks::TestWindowImpl>();
    auto* const pt_test_window_impl = test_window_impl.get();
    auto* const pt_test_ui = test_ui.get();
    const auto window_proxy = std::make_unique<TestBaseWindow>(
            std::move(test_window_impl), std::move(test_ui)
    );
    window_proxy->open();
    EXPECT_CALL(*pt_test_ui, remove_impl());
    EXPECT_CALL(*pt_test_window_impl, close());
    window_proxy->close();
}

TEST(Window, Rendering) {
    auto test_ui = std::make_unique<mocks::TestUI>() ;
    auto test_window_impl = std::make_unique<mocks::TestWindowImpl>();
    auto* const pt_test_window_impl = test_window_impl.get();
    auto* const pt_test_ui = test_ui.get();
    const auto window_proxy = std::make_unique<TestBaseWindow>(
            std::move(test_window_impl), std::move(test_ui)
    );
    window_proxy->open();
    EXPECT_CALL(*pt_test_ui, render_impl());
    EXPECT_CALL(*pt_test_window_impl, render());
    window_proxy->render();
}

TEST(UI, UiAlreadyCreated) {
    auto test_ui = mocks::TestUI() ;
    auto test_window_impl = mocks::TestWindowImpl();
    EXPECT_CALL(test_ui, add_impl()).Times(1);
    test_ui.add(test_window_impl);
    EXPECT_CALL(test_ui, add_impl()).Times(0);
    EXPECT_THROW(
            test_ui.add(test_window_impl),
            ugine::exception::ui::UIAlreadyCreated
    );
}

TEST(UI, UINotCreated) {
    auto test_ui = mocks::TestUI() ;
    auto test_window_impl = mocks::TestWindowImpl();
    EXPECT_CALL(test_ui, render_impl()).Times(0);
    EXPECT_THROW(
            test_ui.render(),
            ugine::exception::ui::UINotCreated
    );
    EXPECT_CALL(test_ui, remove_impl()).Times(0);
    EXPECT_THROW(
            test_ui.remove(),
            ugine::exception::ui::UINotCreated
    );
}
