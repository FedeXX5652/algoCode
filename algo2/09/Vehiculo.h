#ifndef VEHICULO_H
#define VEHICULO_H

class Vehiculo{
    protected:
        unsigned int ruedas;
        bool telepase;
    public:
        Vehiculo(){};

        float montoAPagar(int monto_por_rueda);

        virtual void verificarTelepase(bool is_telepase) = 0;

        virtual void descuento() = 0;
};


class Moto: public Vehiculo{
    public:
        Moto();
        void verificarTelepase(bool telepase):
        float descuento();
};


class Auto: public Vehiculo{
    public:
        Auto();
        void verificarTelepase(bool telepase):
        float descuento();
};


class Camion: public Vehiculo{
    public:
        Camion(unsigned int ruedas);
        void verificarTelepase(bool telepase):
        float descuento();
};

#endif