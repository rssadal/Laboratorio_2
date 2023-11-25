class Relogio{

  int _base_tempo;
  int _temp_base_tempo;
  int _minutos;
  int _horas;
  
  public:
    Relogio(int);
    void tick(void);
    int hora(void);
    int minuto(void);
    void ajuste(int, int);
};
