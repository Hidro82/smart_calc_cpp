#include "interface.h"

namespace s21 {

std::string SMCalcWin::error_codes(int errCode) {
  std::string error;

  if (errCode == 1)
    error = "Zero division!";
  else if (errCode == 2)
    error = "Root of negative number!";
  else if (errCode == 3)
    error = "Not enough numbers!";
  else if (errCode == 4)
    error = "Open the bracket!";
  else if (errCode == 5)
    error = "Close the bracket!";
  else if (errCode == 6)
    error = "Incorrect argument!";
  else if (errCode == 7)
    error = "Too many characters!";
  else if (errCode == 8)
    error = "Bad number!";
  return error;
}

void SMCalcWin::smart_calc() {
  Mathic SMBrain;
  int errCode = 0;
  int X_here = 0;
  double result = 0;
  std::string buffer;
  std::string og = static_cast<std::string>(entry_string->get_text()) + "=";

  for (int i = 0; og[i] != '='; i++)
    if (og[i] == 'X') X_here = 1;
  if (og.length() > 256) {
    errCode = 7;
  } else if (X_here) {
    coor_window(og);
  } else if (!X_here) {
    errCode = SMBrain.stacker(og, 0.0, &result);
    buffer = std::to_string(result);
  }

  if (!errCode && !X_here) {
    entry_string->set_text(buffer);
    sys_label->set_text("Done!");
  } else if (!X_here) {
    sys_label->set_text(error_codes(errCode));
  }
}

void SMCalcWin::button_clicker(const Glib::ustring& data) {
  entry_string->set_text(entry_string->get_text() + data);
  sys_label->set_text("Ready!");
}

void SMCalcWin::clear_button_clicker() {
  entry_string->set_text("");
  sys_label->set_text("Ready!");
}

void SMCalcWin::func_window() {
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("glades/mafs.glade");
  SMCalcFunc* mafs = 0;
  builder->get_widget_derived("mafs_win", mafs);
  mafs->show();
}

void SMCalcWin::credit_window() {
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("glades/credit.glade");
  SMCalcCredit* cred = 0;
  builder->get_widget_derived("cred_win", cred);
  cred->show();
  sys_label->set_text("Credit");
}

void SMCalcWin::coor_window(std::string og) {
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("glades/coor.glade");
  SMCalcCoor* coor = 0;
  builder->get_widget_derived("coor_win", coor);
  coor->show();
  sys_label->set_text("Graph");
  coor->og = og;
  coor->message->set_text(og.substr(0, og.length() - 1));
}

SMCalcWin::SMCalcWin(BaseObjectType* obj,
                     Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj), _builder(builder) {
  _builder->get_widget("entry_string", entry_string);
  _builder->get_widget("one", one);
  _builder->get_widget("two", two);
  _builder->get_widget("three", three);
  _builder->get_widget("four", four);
  _builder->get_widget("five", five);
  _builder->get_widget("six", six);
  _builder->get_widget("seven", seven);
  _builder->get_widget("eight", eight);
  _builder->get_widget("nine", nine);
  _builder->get_widget("zero", zero);
  _builder->get_widget("dot", dot);
  _builder->get_widget("plus", plus);
  _builder->get_widget("minus", minus);
  _builder->get_widget("mult", mult);
  _builder->get_widget("divide", divide);
  _builder->get_widget("mod_button", mod_button);
  _builder->get_widget("power_button", power_button);
  _builder->get_widget("open_bracket", open_bracket);
  _builder->get_widget("close_bracket", close_bracket);
  _builder->get_widget("X_button", X_button);
  _builder->get_widget("clear_button", clear_button);
  _builder->get_widget("math_mod", math_mod);
  _builder->get_widget("credit_start", credit_start);
  _builder->get_widget("calculator", calculator);
  _builder->get_widget("sys_label", sys_label);

  one->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "1"));
  two->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "2"));
  three->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "3"));
  four->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "4"));
  five->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "5"));
  six->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "6"));
  seven->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "7"));
  eight->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "8"));
  nine->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "9"));
  zero->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "0"));
  dot->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "."));
  plus->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "+"));
  minus->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "-"));
  mult->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "*"));
  divide->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "/"));
  mod_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "mod"));
  power_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "^"));
  open_bracket->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "("));
  close_bracket->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), ")"));
  X_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcWin::button_clicker), "X"));
  clear_button->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcWin::clear_button_clicker));
  math_mod->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcWin::func_window));
  credit_start->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcWin::credit_window));
  calculator->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcWin::smart_calc));
}

void SMCalcWin::SMCalcFunc::func_button_clicker(const Glib::ustring& data) {
  entry_string->set_text(entry_string->get_text() + data + "(");
  sys_label->set_text("Ready!");
}

SMCalcWin::SMCalcFunc::SMCalcFunc(BaseObjectType* obj,
                                  Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj), _builder(builder) {
  _builder->get_widget("sin_button", sin_button);
  _builder->get_widget("cos_button", cos_button);
  _builder->get_widget("tan_button", tan_button);
  _builder->get_widget("asin_button", asin_button);
  _builder->get_widget("acos_button", acos_button);
  _builder->get_widget("atan_button", atan_button);
  _builder->get_widget("sqrt_button", sqrt_button);
  _builder->get_widget("log_button", log_button);
  _builder->get_widget("log10_button", log10_button);

  sin_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "sin"));
  cos_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "cos"));
  tan_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "tan"));
  asin_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "asin"));
  acos_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "acos"));
  atan_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "atan"));
  sqrt_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "sqrt"));
  log_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "ln"));
  log10_button->signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &SMCalcFunc::func_button_clicker), "log"));
}

}  // namespace s21