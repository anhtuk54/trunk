#define LOG_TAG "creation_abstract_factory-main"
#include "Logger.h"

#include <memory>

/**
 * @brief Abstract button
 * 
 */
class Button
{
public:
    virtual void create()=0;
};

/**
 * @brief Concrete Button type A
 * 
 */
class ButtonA : public Button
{
public:
    virtual void create() override
    {
        LogInf();
    }
};

/**
 * @brief Concrete Button type B
 * 
 */
class ButtonB : public Button
{
public:
    virtual void create() override
    {
        LogInf();
    }
};

/**
 * @brief Abastract Scrollbar
 * 
 */
class Scrollbar
{
public:
    virtual void create() = 0;
};

/**
 * @brief Concrete Scrollbar type A
 * 
 */
class ScrollbarA : public Scrollbar
{
public:
    void create() override
    {
        LogInf();
    }
};

/**
 * @brief Concrete Scrollbar type B
 * 
 */
class ScrollbarB : public Scrollbar
{
public:
    void create() override
    {
        LogInf();
    }
};

/**
 * @brief Abstract Factory class
 * 
 */
class GUIFactory
{
public:
    virtual std::shared_ptr<Button> createButton()=0;
    virtual std::shared_ptr<Scrollbar> createScrollbar()=0;
};

/**
 * @brief Concrete GUI Factory type A
 * 
 */
class GUIFactoryA: public GUIFactory
{
public:
    std::shared_ptr<Button> createButton()
    {
        std::shared_ptr<Button> button = std::make_shared<ButtonA>();
        button->create();
        return button;
    }

    std::shared_ptr<Scrollbar> createScrollbar()
    {
        std::shared_ptr<Scrollbar> sclbar = std::make_shared<ScrollbarA>();
        sclbar->create();
        return sclbar;
    }
};

/**
 * @brief Concrete GUI Factory type B
 * 
 */
class GUIFactoryB: public GUIFactory
{
public:
    std::shared_ptr<Button> createButton()
    {
        std::shared_ptr<Button> button = std::make_shared<ButtonB>();
        button->create();
        return button;
    }

    std::shared_ptr<Scrollbar> createScrollbar()
    {
        std::shared_ptr<Scrollbar> sclbar = std::make_shared<ScrollbarB>();
        sclbar->create();
        return sclbar;
    }
};

class MyApp
{
public:
    std::shared_ptr<GUIFactory> createGui(const std::string &guiID)
    {
        if (guiID == "A") {
            LogInf() << "Create GUI-A object";
            mGuiRef = std::make_shared<GUIFactoryA>();
        }
        else if (guiID == "B") {
            LogInf() << "Create GUI-B object";
            mGuiRef = std::make_shared<GUIFactoryB>();
        }
        else {
            LogWrn() << "Other ID";
        }
        return mGuiRef;
    }

private:
    std::shared_ptr<GUIFactory> mGuiRef;
};

int main(int argc, char**argv)
{
    MyApp app;
    {
        auto gui = app.createGui("A");
        gui->createButton();
        gui->createScrollbar();
    }

    {
        auto gui = app.createGui("B");
        gui->createButton();
        gui->createScrollbar();
    }
    return 0;
}
