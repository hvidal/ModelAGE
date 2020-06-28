#ifndef PontoQuebraH
#define PontoQuebraH

class PontoQuebra: public TPoint
{
  private:
    // Dono: View do conector a quem este ponto pertence.
    int *IdDono;
  protected:
  public:
    PontoQuebra(): TPoint()
    {
        IdDono = new int;
        *IdDono = -1;
    }
    ~PontoQuebra()
    {
        delete IdDono;
    }

    void SetIdDono(int idDono);
    int GetIdDono();
};
void PontoQuebra::SetIdDono(int idDono)
{
    *IdDono = idDono;
}
int PontoQuebra::GetIdDono()
{
    return *IdDono;
}
#endif