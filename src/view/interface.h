#ifndef SRC_VIEW_INTERFACE_H_
#define SRC_VIEW_INTERFACE_H_

#include <gtkmm.h>

#include <sstream>

#include "../controller/calc.h"

namespace s21 {

static Gtk::Entry *entry_string;
static Gtk::Label *sys_label;

class SMCalcCredit : public Gtk::ApplicationWindow {
 public:
  void credit_proc();

  SMCalcCredit(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

 private:
  Glib::RefPtr<Gtk::Builder> _builder;
  Gtk::Entry *credit_entry;
  Gtk::Entry *percent_entry;
  Gtk::Entry *time_amount;
  Gtk::Switch *diff_switch;
  Gtk::Switch *time_type;
  Gtk::Button *start_button;
  Gtk::Label *cred_res;
  Gtk::Label *cr_pay;
  Gtk::Label *cr_over;
};

class SMCalcWin : public Gtk::ApplicationWindow {
  class SMCalcFunc : public Gtk::ApplicationWindow {
   public:
    void func_button_clicker(const Glib::ustring &data);
    SMCalcFunc(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

   private:
    Glib::RefPtr<Gtk::Builder> _builder;
    Gtk::Button *sin_button;
    Gtk::Button *cos_button;
    Gtk::Button *tan_button;
    Gtk::Button *asin_button;
    Gtk::Button *acos_button;
    Gtk::Button *atan_button;
    Gtk::Button *sqrt_button;
    Gtk::Button *log_button;
    Gtk::Button *log10_button;
  };

  class SMCalcCoor : public Gtk::ApplicationWindow {
    friend class SMCalcWin;

    class SMCalcGraph : public Gtk::ApplicationWindow {
      friend class SMCalcCoor;

     public:
      SMCalcGraph(BaseObjectType *obj,
                  Glib::RefPtr<Gtk::Builder> const &builder);

     protected:
      bool on_draw(Cairo::RefPtr<Cairo::Context> const &cr) override;
      void grid_maker(Cairo::RefPtr<Cairo::Context> const &cr);
      void line_drawer(Cairo::RefPtr<Cairo::Context> const &cr);

     private:
      std::string og;
      CoorData *dat;
      Glib::RefPtr<Gtk::Builder> _builder;
      Gtk::Window *graph_win;
      Gtk::DrawingArea *canvas;
    };

   public:
    void graph_window();

    SMCalcCoor(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

   private:
    std::string og;
    Glib::RefPtr<Gtk::Builder> _builder;
    Gtk::Button *start_button;
    Gtk::Entry *x_1;
    Gtk::Entry *x_2;
    Gtk::Entry *y_1;
    Gtk::Entry *y_2;
    Gtk::Label *message;
  };

 public:
  std::string error_codes(int errCode);
  void smart_calc();
  void button_clicker(const Glib::ustring &data);
  void clear_button_clicker();
  void func_window();
  void credit_window();
  void coor_window(std::string og);

  SMCalcWin(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

 private:
  Glib::RefPtr<Gtk::Builder> _builder;
  Gtk::Button *calculator;
  Gtk::Button *one;
  Gtk::Button *two;
  Gtk::Button *three;
  Gtk::Button *four;
  Gtk::Button *five;
  Gtk::Button *six;
  Gtk::Button *seven;
  Gtk::Button *eight;
  Gtk::Button *nine;
  Gtk::Button *zero;
  Gtk::Button *dot;
  Gtk::Button *plus;
  Gtk::Button *minus;
  Gtk::Button *mult;
  Gtk::Button *divide;
  Gtk::Button *mod_button;
  Gtk::Button *power_button;
  Gtk::Button *open_bracket;
  Gtk::Button *close_bracket;
  Gtk::Button *X_button;
  Gtk::Button *clear_button;
  Gtk::Button *math_mod;
  Gtk::Button *credit_start;
};

}  // namespace s21

#endif  // SRC_VIEW_INTERFACE_H_
