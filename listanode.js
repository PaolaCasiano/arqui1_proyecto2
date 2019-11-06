class ListaEcuaciones {
  constructor() {
	this.actual = null;
	this.primera = null;
	this.ultima = null;
  }

  imprimir(){
	  if(this.primera==null){
		return 'Lista de ecuaciones Vacia';
	  }else{
		  var aux = this.primera;
		  var str = "[" + this.primera.ecuacion+']';
		  while(aux.siguiente != null){
			aux = aux.siguiente;
			str += '>>>>>[' + aux.ecuacion+'] \n<br>';
			str += ' 	x->[' + aux.eqx+'] \n<br>';
			str += ' 	y->[' + aux.eqy+'] \n<br>';
			str += ' 	z->[' + aux.eqz+'] \n<br>';

		  }
		  return str;
	  }
  }



  addEcuacion (ecuacion, xi, xs, yi, ys, zi, zs, eqx, eqy, eqz){
	var nueva = new Ecuacion(ecuacion, xi, xs, yi, ys, zi, zs, eqx, eqy, eqz);
	if(this.primera == null){
	  this.primera = nueva;
	  this.ultima = this.primera;
	  this.actual = this.primera;
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
	constructor(ecuacion, xi, xs, yi, ys, zi, zs, eqx, eqy, eqz){
		this.ecuacion = ecuacion;
		this.xi = xi;
		this.xs = xs;
		this.yi = yi;
		this.ys = ys;
		this.zi = zi;
		this.zs = zs;
		this.siguiente = null;
		this.anterior = null;
		this.eqx = eqx;
		this.eqy = eqy;
		this.eqz = eqz;

	}

	setSiguiente(siguiente) {
	  this.siguiente = siguiente;
	}

	setanterior(anterior){
	  this.anterior = anterior;
	}

	setAxis(x, y, z){
		this.x = x;
		this.y = y;
		this.z = z;
	}

	getPuntos(){
		response = [];
		return response;
	}
}



