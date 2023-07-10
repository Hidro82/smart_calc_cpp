#include "interface.h"

namespace s21 {

void SMCalcCredit::credit_proc() {
  Credit CrBrain;
  std::string buffer;
  int errCode = 0;
  std::ostringstream ss1;
  std::ostringstream ss2;
  std::ostringstream ss3;
  std::ostringstream ss4;

  CrBrain.input_handler(
      std::stof(static_cast<std::string>(credit_entry->get_text())),
      std::stoi(static_cast<std::string>(time_amount->get_text())),
      static_cast<int>(time_type->get_state()),
      std::stof(static_cast<std::string>(percent_entry->get_text())),
      static_cast<int>(diff_switch->get_state()));

  errCode = CrBrain.credit_calculus();

  if (!errCode) {
    ss1 << CrBrain.output_whole();
    buffer = ss1.str();
    cred_res->set_text(buffer);
    if (static_cast<int>(diff_switch->get_state())) {
      ss2 << CrBrain.output_month_1();
      ss3 << CrBrain.output_month_2();
      buffer = ss2.str() + ".." + ss3.str();
      cr_pay->set_text(buffer);
    } else {
      ss2 << CrBrain.output_month_1();
      buffer = ss2.str();
      cr_pay->set_text(buffer);
    }
    ss4 << CrBrain.output_over();
    buffer = ss4.str();
    cr_over->set_text(buffer);
  }
}

SMCalcCredit::SMCalcCredit(BaseObjectType* obj,
                           Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj), _builder(builder) {
  _builder->get_widget("credit_entry", credit_entry);
  _builder->get_widget("percent_entry", percent_entry);
  _builder->get_widget("time_amount", time_amount);
  _builder->get_widget("diff_switch", diff_switch);
  _builder->get_widget("time_type", time_type);
  _builder->get_widget("start_button", start_button);
  _builder->get_widget("cred_res", cred_res);
  _builder->get_widget("cr_pay", cr_pay);
  _builder->get_widget("cr_over", cr_over);

  start_button->signal_clicked().connect(
      sigc::mem_fun(*this, &SMCalcCredit::credit_proc));
}

}  // namespace s21