#include "relogio.h"

Relogio::Relogio(int base_tempo) {
  _base_tempo = base_tempo;
  _temp_base_tempo = _base_tempo;

}

void Relogio::tick(void) {

  _temp_base_tempo--;
  if (_temp_base_tempo <= 0) {
    _temp_base_tempo = _base_tempo;
    _minutos++;
    if (_minutos == 60) {
      _minutos = 0;
      _horas++;
      if (_horas == 24) {
        _horas = 0;
      }
    }
  }
}

int Relogio::hora(void) {
  return _horas;
}

int Relogio::minuto(void) {
  return _minutos;
}

void Relogio::ajuste(int horas, int minutos) {
  if (horas > 0 || horas < 24) {
    _horas = horas;
  }
  if (minutos > 0 || minutos < 60) {
    _minutos = minutos;
  }
}
