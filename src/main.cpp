#include <iostream>

#include "controller.hpp"
#include "document.hpp"
#include "view.hpp"

void handle_gui_create_new(Controller& controller) { controller.handle_create_new_document(); }

void handle_gui_add_circle(Controller& controller)
{
	double radius;
	std::cout << "Enter radius for Circle: ";
	std::cin >> radius;
	controller.handle_add_circle(radius);
}

void handle_gui_add_rectangle(Controller& controller)
{
	double w, h;
	std::cout << "Enter width for Rectangle: ";
	std::cin >> w;
	std::cout << "Enter height for Rectangle: ";
	std::cin >> h;
	controller.handle_add_rectangle(w, h);
}

void handle_gui_remove_shape(Controller& controller)
{
	size_t index;
	std::cout << "Enter index of shape to remove: ";
	std::cin >> index;
	controller.handle_remove_shape(index);
}

void handle_gui_save(Controller& controller)
{
	std::string filename = "document.dat";
	controller.handle_save(filename);
}

void handle_gui_load(Controller& controller)
{
	std::string filename = "document.dat";
	controller.handle_load(filename);
}

void handle_gui_render(Controller& controller) { controller.handle_render(); }

int main()
{
	Document doc;
	View view(doc);
	Controller controller(doc, view);

	size_t choice = 0;
	do {
		view.show_menu();
		std::cin >> choice;

		switch (choice) {
			case 1:
				handle_gui_create_new(controller);
				break;
			case 2:
				handle_gui_add_circle(controller);
				break;
			case 3:
				handle_gui_add_rectangle(controller);
				break;
			case 4:
				handle_gui_remove_shape(controller);
				break;
			case 5:
				handle_gui_save(controller);
				break;
			case 6:
				handle_gui_load(controller);
				break;
			case 7:
				handle_gui_render(controller);
				break;
			case 8:
				std::cout << "Exiting..." << std::endl;
				break;
			default:
				std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 8);

	return 0;
}