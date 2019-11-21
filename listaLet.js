

class ListaLetras {
  constructor() {
    this.actual = null;
    this.primera = null;
    this.ultima = null;
  }


  getLetras(){
    //"hello".split('').join(' ');
	  return '~'+this.actual.letras.toLowerCase().replace(/Ñ|ñ/gi,"~").split('').join(' ');
  }

  moveActual(){
	  this.actual = this.actual.siguiente
  }

  imprimir(){
    if(this.primera==null){
      return 'Lista de Frases Vacia';
      }else{
        var aux = this.primera;
        var str = "[" + this.primera.letras+']\n <br>';
        while(aux.siguiente != null){
        aux = aux.siguiente;
        str += ' ->[' + aux.letras+'] \n<br>';
        }
        return str;
      }
  }

  vaciarLista(){
    this.actual = null;
    this.primera = null;
    this.ultima = null;
  }



  addLetras (letras){
    var nueva = new Letrero(letras);
    if(this.primera == null){
      this.primera = nueva;
      this.ultima = this.primera;
      this.actual = this.primera;
    }else{
      this.ultima.siguiente = nueva;
      this.ultima = this.ultima.siguiente
      if(this.actual == null){
        this.actual = this.ultima;
      }
    }
  }


  returnxml(){
    var xml = '<queryresult success="true" error="false" numpods="4" datatypes="Solve" timedout="" timedoutpods="" timing="1.544" parsetiming="0.68" parsetimedout="false" recalculate="" id="MSP68133e37cb32hhh6c300004e98ea55d8ada70c" host="https://www4f.wolframalpha.com" server="22" related="https://www4f.wolframalpha.com/api/v1/relatedQueries.jsp?id=MSPa69133e37cb32hhh6c300002ffe1e84i2a12ef02121523691492368303" version="2.6">'+
    '<pod title="Input interpretation" scanner="Identity" id="Input" position="100" error="false" numsubpods="1">'+
    '<subpod title="">'+
    '<img src="https://www4f.wolframalpha.com/Calculate/MSP/MSP70133e37cb32hhh6c300002dfbafia59da44hi?MSPStoreType=image/gifs=22" alt="solve 3 x - 7 = 11 for x" title="solve 3 x - 7 = 11 for x" width="256" height="32" type="Grid" themes="1,2,3,4,5,6,7,8,9,10,11,12" colorinvertable="true"/>'+
    '<plaintext>solve 3 x - 7 = 11 for x</plaintext>'+
    '</subpod>'+
    '<expressiontypes count="1">'+
    '<expressiontype name="Default"/>'+
    '</expressiontypes>'+
    '</pod>'+
    '<pod title="Result" scanner="Solve" id="Result" position="200" error="false" numsubpods="1" primary="true">'+
    '<subpod title="">'+
    '<img src="https://www4f.wolframalpha.com/Calculate/MSP/MSP71133e37cb32hhh6c300005ge1gga758b2632f?MSPStoreType=image/gifs=22" alt="x = 6" title="x = 6" width="34" height="18" type="Default" themes="1,2,3,4,5,6,7,8,9,10,11,12" colorinvertable="true"/>'+
    '<plaintext>x = 6</plaintext>'+
    '</subpod>'+
    '<expressiontypes count="1">'+
    '<expressiontype name="Default"/>'+
    '</expressiontypes>'+
    '<states count="1">'+
    '<state name="Step-by-step solution" input="Result__Step-by-step solution" stepbystep="true"/>'+
    '</states>'+
    '</pod>'+
    '<pod title="Plot" scanner="Solve" id="RootPlot" position="300" error="false" numsubpods="1">'+
    '<subpod title="">'+
    '<img src="https://www4f.wolframalpha.com/Calculate/MSP/MSP72133e37cb32hhh6c3000054cbcf4h3176g94i?MSPStoreType=image/gifs=22" alt="" title="" width="393" height="206" type="2DMathPlot_1" themes="1,2,3,4,5,6,7,8,9,10,11,12" colorinvertable="true"/>'+
    '<plaintext/>'+
    '</subpod>'+
    '<expressiontypes count="1">'+
    '<expressiontype name="Default"/>'+
    '</expressiontypes>'+
    '</pod>'+
    '<pod title="Number line" scanner="Solve" id="NumberLine" position="400" error="false" numsubpods="1">'+
    '<subpod title="">'+
    '<img src="https://www4f.wolframalpha.com/Calculate/MSP/MSP73133e37cb32hhh6c300001h97hf21aa104010?MSPStoreType=image/gifs=22" alt="" title="" width="330" height="58" type="1DMathPlot_1" themes="1,2,3,4,5,6,7,8,9,10,11,12" colorinvertable="true"/>'+
    '<plaintext/>'+
    '</subpod>'+
    '<expressiontypes count="1">'+
    '<expressiontype name="1DMathPlot"/>'+
    '</expressiontypes>'+
    '</pod>'+
    '</queryresult>'
    ;

    return xml;
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

    set_anterior(anterior){
      this.anterior = anterior;
    }
}

