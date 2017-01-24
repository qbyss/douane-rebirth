// req: libnotifymm, libnotifymm-devel
#include <iostream>
#include <gtkmm.h>
#include <libnotifymm.h>

using namespace std;

string appname;

void AccessCallback(const Glib::ustring & answer)
{
	if(answer == "allow")
	{
		cout << "Allowing the application " << appname << " to access the internet" << endl;
	}
	else if(answer == "deny")
	{
		cout << "Denying the application " << appname << " to access the internet" << endl;
	}

	// Force quit the application
	gtk_main_quit();
}

int main(int argc, char *argv[]) {
	Notify::init("Douane notification");
	sigc::slot<void, const Glib::ustring&> sl = sigc::ptr_fun(&AccessCallback);

	cout << "Initializing app (" << argc << ")" << endl;
	if(argc > 1)
	{
		cout << "Apps that needs application : " << argv[1] << endl;
		appname = argv[1];
	}
	else
	{
		appname = "undefined";
	}

	// Display a notification
	Notify::Notification n("Douane", "An application would like to access the internet", "dialog-information");
	n.add_action("allow", "Allow", sl);
	n.add_action("deny", "Forbid", sl);
	n.set_timeout(0);
	n.show();

	gtk_init(&argc, &argv);	// args unused
	gtk_main();		// infinite loop

	return 0;
}
