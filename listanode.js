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
		var str = ">>>>>[" + this.primera.ecuacion+'] \n<br>';
		str += ' 	x->[' + this.primera.eqx+'] \n<br>';
		str += ' 	y->[' + this.primera.eqy+'] \n<br>';
		str += ' 	z->[' + this.primera.eqz+'] \n<br>';
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

  vaciarLista(){
  	this.actual = null;
	this.primera = null;
	this.ultima = null;
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

	getTipo(){
		var yto2 		= this.eqz.match(/y\^2/g);
		var xto2 		= this.eqz.match(/x\^2/g);
		var justx		= this.eqz.match(/x/g);
		var justy		= this.eqz.match(/y/g);
		var sqrt		= this.eqz.match(/sqrt/g);
		var coma 		= this.eqz.match(/,/g);

		/*
		C CONO
			S ESFERA
			P PLANO
			B PARABOLOIDE
		H HIPERBOLOIDE1
		J HIPERBOLOIDE2
			L CILINTRO
		*/

		if(this.eqx == ""  || this.eqy == "" || this.eqz == ""){
			return "L";
		}

		if(justx.length == 4 && justy.length == 4 && sqrt.length == 2){
			return "S";
		}

		if(xto2.length == 0 && yto2.length == 0 && sqrt.length == 0){
			return "P";
		}

		var x2y = (xto2.length == 1 && yto2.length == 0 && justy.length == 1);
		var y2x = (yto2.length == 1 && xto2.length == 0 && justx.length == 1);
		if(sqrt.length == 2 && (x2y || y2x)){
			return "B";
		}else if(coma.length == 0 && (yto2.length == 0 && justy.length == 1 || xto2.length == 0 && justx.length == 1)){
			return "B";
		}

		return "J";

	}


}



