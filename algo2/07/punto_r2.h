#ifndef PUNTO_R2_H_INCLUDED
#define PUNTO_R2_H_INCLUDED

class PuntoR2{
    // Atributos
    private:
        double x;
        double y;
    
    // Metodos
    public:
        /*
        Constructor sin parametros
        Pre: 
        Post: construye un PuntoR2 con (0,0)
        */
       PuntoR2();   // no le paso parametros, tiene que llevar el mismo nombre que la clase y no retorna nada, van en public

        /*
        Constructor con parametros
        Pre: 
        Post: construye un PuntoR2 con (cx,cy)
        */
       PuntoR2(double x, double y);   // le paso parametros, tiene que llevar el mismo nombre que la clase y no retorna nada, van en public


        /*
        Asigna el valor de cx a la primera coordenada
        Pre: -
        Post: asigna cx a la primera coordenada
        */
        void asignar_x(double cx);

        /*
        Asigna el valor de cy a la segunda coordenada
        Pre: -
        Post: asigna cy a la segunda coordenada
        */
        void asignar_y(double cy);

        /*
        Devuelve el valor de la primera coordenada
        Pre: -
        Post: devuelve el valor de la primera coordenada
        */
        double obtener_x();

        /*
        Devuelve el valor de la segunda coordenada
        Pre: -
        Post: devuelve el valor de la segunda coordenada
        */
        double obtener_y();

        void mostrar();

        /*
        Destructor
        Pre: 
        Post: 
        */
       ~PuntoR2();
};

#endif // PUNTO_R2_H_INCLUDED