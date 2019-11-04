class ListaEcuaciones {
  constructor() {
    this.actual = null;
    this.primera = null;
    this.ultima = null;
  }



  addEcuacion (ecuacion, xi, xs, yi, ys, zi, zs){
    nueva = new Ecuacion(ecuacion, xi, xs, yi, ys, zi, zs);
    if(this.primera == null){
      this.primera = nueva;
      this.ultima = this.primera;
      this.actual = primera;
    }else{
      this.ultima.siguiente = nueva;
      this.ultima = this.ultima.siguiente
    }
  }

  getActual(){
	return this.actual;
  }

  moveActual(){
	  this.actual = this.actual.siguiente
  }



}

module.exports = ListaEcuaciones;

class Ecuacion{
    constructor(ecuacion, xi, xs, yi, ys, zi, zs){
        this.ecuacion = ecuacion;
        this.xi = xi;
        this.xs = xs;
        this.yi = yi;
        this.ys = ys;
        this.zi = zi;
        this.zs = zs;
        this.siguiente = null;
        this.anterior = null;

    }

    setSiguiente(siguiente) {
      this.siguiente = siguiente;
    }

    set anterior(anterior){
      this.anterior = anterior;
    }

    setAxis(x, y, z){
        this.x = x;
        this.y = y;
        this.z = z;
    }

    getPuntos(){
        
    }
}



