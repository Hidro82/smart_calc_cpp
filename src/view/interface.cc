#include "interface.h"

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("glades/smc.glade");
  s21::SMCalcWin* smc = 0;
  builder->get_widget_derived("window", smc);
  app.run(*smc);
  delete smc;
  return 0;
}
