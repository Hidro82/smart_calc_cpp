#include "interface.h"

namespace s21 {

void SMCalcWin::SMCalcCoor::graph_window() {
  double xd_1 = std::stof(static_cast<std::string>(x_1->get_text()));
  double yd_1 = std::stof(static_cast<std::string>(y_1->get_text()));
  double xd_2 = std::stof(static_cast<std::string>(x_2->get_text()));
  double yd_2 = std::stof(static_cast<std::string>(y_2->get_text()));
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("glades/graph.glade");
  SMCalcGraph* graph = 0;
  builder->get_widget_derived("graph_win", graph);
  graph->show();
  graph->dat = new CoorData(xd_1, xd_2, yd_1, yd_2);
  graph->og = og;
}

SMCalcWin::SMCalcCoor::SMCalcCoor(BaseObjectType* obj,
                                  Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj), _builder(builder) {
  _builder->get_widget("message", message);
  _builder->get_widget("x_1", x_1);
  _builder->get_widget("x_2", x_2);
  _builder->get_widget("y_1", y_1);
  _builder->get_widget("y_2", y_2);
  _builder->get_widget("start_button", start_button);

  start_button->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcCoor::graph_window));
}

SMCalcWin::SMCalcCoor::SMCalcGraph::SMCalcGraph(
    BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj), _builder(builder) {
  _builder->get_widget("canvas", canvas);
  _builder->get_widget("graph_win", graph_win);

  graph_win->set_default_size(300, 300);
}

bool SMCalcWin::SMCalcCoor::SMCalcGraph::on_draw(
    Cairo::RefPtr<Cairo::Context> const& cr) {
  grid_maker(cr);
  line_drawer(cr);
  return true;
}

void SMCalcWin::SMCalcCoor::SMCalcGraph::grid_maker(
    Cairo::RefPtr<Cairo::Context> const& cr) {
  double offset = 0;
  char num[10];
  cr->set_source_rgb(1.0, 1.0, 1.0);
  cr->paint();
  cr->stroke();
  cr->set_source_rgb(0.0, 1.0, 0.0);
  cr->set_line_width(0.5);
  offset = dat->x_zero + 30;
  while (offset < 300) {
    cr->move_to(offset, 0);
    cr->line_to(offset, 300);
    cr->stroke();
    if (dat->y_zero > 30)
      cr->move_to(offset, dat->y_zero - 5);
    else
      cr->move_to(offset, dat->y_zero + 10);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    gcvt((offset - dat->x_zero) / dat->x_scale, 6, num);
    cr->show_text(num);
    cr->stroke();
    cr->set_source_rgb(0.0, 1.0, 0.0);
    offset += 30;
  }
  offset = dat->x_zero - 30;
  while (offset > 0) {
    cr->move_to(offset, 0);
    cr->line_to(offset, 300);
    cr->stroke();
    if (dat->y_zero > 30)
      cr->move_to(offset, dat->y_zero - 5);
    else
      cr->move_to(offset, dat->y_zero + 10);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    gcvt((offset - dat->x_zero) / dat->x_scale, 6, num);
    cr->show_text(num);
    cr->stroke();
    cr->set_source_rgb(0.0, 1.0, 0.0);
    offset -= 30;
  }
  offset = dat->y_zero + 30;
  while (offset < 300) {
    cr->move_to(0, offset);
    cr->line_to(300, offset);
    cr->stroke();
    if (dat->x_zero > 30)
      cr->move_to(dat->x_zero - 10, offset);
    else
      cr->move_to(dat->x_zero + 5, offset);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    gcvt(-(offset - dat->y_zero) / dat->y_scale, 6, num);
    cr->show_text(num);
    cr->stroke();
    cr->set_source_rgb(0.0, 1.0, 0.0);
    offset += 30;
  }
  offset = dat->y_zero - 30;
  while (offset > 0) {
    cr->move_to(0, offset);
    cr->line_to(300, offset);
    cr->stroke();
    if (dat->x_zero > 30)
      cr->move_to(dat->x_zero - 10, offset);
    else
      cr->move_to(dat->x_zero + 5, offset);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    gcvt(-(offset - dat->y_zero) / dat->y_scale, 6, num);
    cr->show_text(num);
    cr->stroke();
    cr->set_source_rgb(0.0, 1.0, 0.0);
    offset -= 30;
  }
  cr->stroke();

  cr->set_line_width(1.0);
  cr->set_source_rgb(1.0, 0.0, 0.0);
  cr->move_to(0, dat->y_zero);
  cr->line_to(300, dat->y_zero);
  cr->move_to(dat->x_zero, 0);
  cr->line_to(dat->x_zero, 300);
  cr->stroke();
}

void SMCalcWin::SMCalcCoor::SMCalcGraph::line_drawer(
    Cairo::RefPtr<Cairo::Context> const& cr) {
  Mathic SMBrain;
  int errCode = 0;
  double x = dat->x_start;
  double y = 0;

  cr->set_source_rgb(0.0, 0.0, 1.0);
  if (dat->x_start > dat->x_end) errCode = 8;
  while ((x <= dat->x_end) && !errCode) {
    errCode = SMBrain.stacker(og, x, &y);
    if ((x == dat->x_start) && !errCode) {
      cr->move_to((x * dat->x_scale) + dat->x_zero,
                  dat->y_zero - (y * dat->y_scale));
    } else if (!errCode) {
      cr->line_to((x * dat->x_scale) + dat->x_zero,
                  dat->y_zero - (y * dat->y_scale));
    }
    if ((errCode == 1) || (errCode == 2) || (errCode == 6)) {
      errCode = 0;
      dat->x_start = x;
    }
    x += dat->x_step;
  }
  cr->stroke();
}

}  // namespace s21