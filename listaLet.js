

class ListaLetras {
  constructor() {
    this.actual = null;
    this.primera = null;
    this.ultima = null;
  }



  addetras (letras){
    nueva = new Letrero(letras);
    if(this.primera == null){
      this.primera = nueva;
      this.ultima = this.primera;
    }else{
      this.ultima.siguiente = nueva;
      this.ultima = this.ultima.siguiente
    }
  }
}

module.exports = ListaLetras;

class Letrero{
    constructor(letras){
        this.letras = letras;
        this.siguiente = null;
        this.anterior = null;

    }

    setSiguiente(siguiente) {
      this.siguiente = siguiente;
    }

    set anterior(anterior){
      this.anterior = anterior;
    }
}

