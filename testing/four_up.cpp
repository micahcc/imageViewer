#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WLink>
#include <Wt/WText>


using namespace Wt;

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class FourUpDisplay: public WApplication
{
public:
    FourUpDisplay(const WEnvironment& env);

private:
    Wt::WContainerWidget* container;
    Wt::WText* textOut;
    Wt::WImage* primaryImage;

    void onclicked(const Wt::WMouseEvent& e);
};

void FourUpDisplay::onclicked(const Wt::WMouseEvent& e)
{
    textOut->setText("You clicked the Wt logo at "
            "(" + boost::lexical_cast<std::string>(e.widget().x) +
            "," + boost::lexical_cast<std::string>(e.widget().y) +
            ").");
}

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
 */
FourUpDisplay::FourUpDisplay(const WEnvironment& env) : WApplication(env)
{
    setTitle("Showing four generated images."); 

    container = new Wt::WContainerWidget();
    root()->addWidget(container);

    primaryImage = new Wt::WImage(Wt::WLink("data/test.svg"), container);
    primaryImage->setAlternateText("Image!");

    textOut = new Wt::WText(container);
    textOut->setMargin(10, Wt::Left);

    primaryImage->clicked().connect(this, &FourUpDisplay::onclicked);
}

WApplication *createApplication(const WEnvironment& env)
{
    /*
     * You could read information from the environment to decide whether
     * the user has permission to start a new application
     */
    return new FourUpDisplay(env);
}

int main(int argc, char **argv)
{
    /*
     * Your main method may set up some shared resources, but should then
     * start the server application (FastCGI or httpd) that starts listening
     * for requests, and handles all of the application life cycles.
     *
     * The last argument to WRun specifies the function that will instantiate
     * new application objects. That function is executed when a new user surfs
     * to the Wt application, and after the library has negotiated browser
     * support. The function should return a newly instantiated application
     * object.
     */
    return WRun(argc, argv, &createApplication);
}

