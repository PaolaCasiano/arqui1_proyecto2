var express = require('express')
var http = require('http')
const https = require('https');
var app = express()
var ListaEcuaciones = require('./listanode')
var ListaLetras = require('./listaLet')
var nerdamer = require('nerdamer')
var solve = require('./Solve')
let xmlParser = require('xml2json')
var fs = require('fs');
var math = require('mathjs')
//ESTADOS
//1 ESCRITORIO
//2 MOVIL
//api link http://api.wolframalpha.com/v2/query?input=solve+3x-7%3D11for+x&appid=LVALQJ-UPG9XXATRG
//http://api.wolframalpha.com/v2/query?input=solve+{{ecuacion lado 1}}%3D{{ecuacion igual a}}for+{{Variable a despejar}}&appid=LVALQJ-UPG9XXATRG

var lista 		= new ListaEcuaciones()
var letras 		=  new ListaLetras()
var estado 		= 1
var paso 		= 0.5;
var no_puntos 	= 100;
var unidadx 	= 1;
var unidady 	= 1;
var axisH   	= 200;
var axisV  		= 0;
var ancho 		= 320;
var alto 		= 200;

var modo_movil = 'D';

app.get('/guardar_funcion', function (req, res) {
	var posB = req.query;
	var assembly = posB.eq.split(';');

	if(assembly.length >0){
		var equation = assembly[0];
		equation = equation.replace(/ /g, "");
		var eqx = getEqAxis(equation, 'x');
		var eqy = getEqAxis(equation, 'y');
		var eqz = getEqAxis(equation, 'z');	

		var limx = assembly[1].split(',');
		var limy = assembly[2].split(',');
		var limz = assembly[3].split(',');
		lista.addEcuacion(
					equation
					, limx[0]
					, limx[1]
					, limy[0]
					, limy[1]
					, limz[0]
					, limz[1]
					, eqx
					, eqy
					, eqz
					);	
		res.send('se guardo ecuacion');
	}
	
	
 });

 app.post('/guardar_letras', function(req,res){
	var postB = req.query;
	//console.log(req);
	letras.addLetras(postB.letras);
	res.send('se ha guardado');
 });

 app.get('/guardar_letras', function(req,res){
	var postB = req.query;
	console.log(req.query);
	letras.addLetras(postB.letras);
	res.send('se ha guardado');
 });

 app.get('/cambiar_movil', function(req,res){
	estado = 2;
	modo_movil= 'A';
	res.send('A');
 });

 app.get('/imprimir', function(req,res){
	var str = imprimirListas();
	res.send(str);
 });

 app.get('/prueba_figura', function(req,res){
	var str = prueba_figura();
	res.send(str);
 });

 app.get('/', function(req,res){
	let data = '';
	data = letras.returnxml();
	var jsonstr = xmlParser.toJson(data);
	var json = JSON.parse(jsonstr);
	res.send('Bienvenido a mi server :3');
 });

 app.get('/get_estado', function(req,res){
 	//console.log(modo_movil);
	res.send(modo_movil);
 });

 app.get('/borrarListaEcuaciones', function(req,res){
	lista.vaciarLista();
 });

 app.get('/borrarListaTexto', function(req,res){
	letras.vaciarLista();
 });

 app.get('/cambiar_escritorio', function(req, res){
	modo_movil = 'D';	
	res.send('D');
 });

 app.get('/prueba',function(req, res){
 	var ecuaciones = [
	 	'z^2 = (4+5*2)*x^2 + (4+5*3/2)*y^2'
		, '(x-(4+5/6*5))^2 + (y-(5*2+5))^2 + (z-(1*2+3*4))^2 = (2+2)^2'
		//, 'x/(4+5/6*5) + y/(5*2+5) + z/(1*2+3*4) = 1'
		//, 'z = x^2 + y ^2'
		//, '-x^2/(4+5/6*5)^2 + y^2/(5*2+5)^2 + z^2/(1*2+3*4)^2 = 1'
		//, '-x^2/(4+5/6*5)^2 + y^2/(5*2+5)^2 - z^2/(1*2+3*4)^2 = 1'
		//, 'x^2 + y^2 = (2+2)^2'
		];

	var posB = {
		'xi': '-10'
		, 'xs': '10'
		, 'yi': '-10'
		, 'ys': '10'
		, 'zi': '-10'
		, 'zs': '10'
	};

		var equation = "";
	for (var i = 0; i < ecuaciones.length; i++) {
		equation = ecuaciones[i]; 	
		equation = equation.replace(/ /g, "");
		//res.send(equation);
		//return;
		console.log(equation);
		var eqx = getEqAxis(equation, 'x');
		var eqy = getEqAxis(equation, 'y');
		var eqz = getEqAxis(equation, 'z');
		lista.addEcuacion(
					equation
					, posB.xi
					, posB.xs
					, posB.yi
					, posB.ys
					, posB.zi
					, posB.zs
					, eqx
					, eqy
					, eqz
					);	
	}

	/*var posB = {
		'equ':'(x^2/4) + (y^2/8+2) + z^2 = 2^2 * 1'
		, 'xi': '-10'
		, 'xs': '10'
		, 'yi': '-10'
		, 'ys': '10'
		, 'zi': '-10'
		, 'zs': '10'
	};
	
	var equation = posB.equ;
	equation = equation.replace(/ /g, "");*/
	//res.send(equation);
	//return;
	/*var eqx = getEqAxis(equation, 'x');
	var eqy = getEqAxis(equation, 'y');
	var eqz = getEqAxis(equation, 'z');
	lista.addEcuacion(
				posB.equ
				, posB.xi
				, posB.xs
				, posB.yi
				, posB.ys
				, posB.zi
				, posB.zs
				, eqx
				, eqy
				, eqz
				);	*/
	var imprime = imprimirListas();
	imprime += '<br><br>\n \n' + getPuntos(lista.primera, 'x-y', 0);
	res.send(imprime);
 });

app.get('/getUltimaEcuacion2D', (req, res) => {	
	var codigo = 0;
	var mensaje = '';
	var eq = 'E';//envio caracter E para indicar al modulo que la lista esta vacia
	var axis = req.query;
	var ejes = axis.ejes;

	if(lista.ultima == null){
		codigo = 2;
		mensaje = 'Lista de ecuaciones vacia';
	}else{
		var equa = lista.ultima;
		eq = getPuntos(equa, ejes, 0);
	}

	var response = {
		'codigo': codigo
		, 'mensaje':mensaje
	};
	console.log(response);
  	res.send(eq);
});

app.get('/getEcuacionActual3D', (req, res)=>{
	var eq = "E";
	if(lista.ultima != null){
		console.log(lista.ultima.ecuacion);
		eq = lista.ultima.getTipo();
	}
  	res.send(eq);
});

app.get('/getUltimoTexto', (req, res) => {
	var codigo = 0;
	var mensaje = '';
	var eq = '';
	
	if(letras.actual == null){
		eq = '';
	}else{
		eq = letras.getLetras();
		letras.moveActual();
	}
	
	var response = {
		'codigo': codigo
		, 'mensaje':mensaje
		, 'puntos': eq
	};
	console.log(response);
  	res.send(eq);
});

function imprimirListas(){
	var str = lista.imprimir();
	str += '  \n <br>';
	str += letras.imprimir();
	return str;
}

function prueba_figura(argument) {
	if(lista.ultima != null){
		return lista.ultima.esCono();
	}
}


function getEqAxis(eq, axis){
	var ecuacion = eq;
	ecuacion = ecuacion.replace(/ /g, "");
	var command = nerdamer.solveEquations(ecuacion,axis);
	return command.toString();


	//esta es la llamada a la api, con las 4 lineas de codigo de arriba ya no es necesario.. a no serrr
	var url = 'http://api.wolframalpha.com/v2/query?input=solve+'+ecuacion[0]+'%3D'+ecuacion[1]+'for+'+axis+'&appid=LVALQJ-UPG9XXATRG';
	console.log(url);
	var filename = eq.replace(/ /g, "");
			filename = filename.replace('\\','');	
			filename = filename.replace('/','');	
			filename = filename.replace('\/','');	
			filename = filename.replace(':','');	
			filename = filename.replace('*','');	
			filename = filename.replace('?','');	
			filename = filename.replace('"','');	
			filename = filename.replace('>','');	
				filename = filename.replace('<','');	
			filename = filename.replace('|','');
			filename = 'eq_'+filename+'_'+axis+'.txt'	
	console.log(filename);

	http.get(url, (resp) => {
		var data = '';
		resp.on('data', (chunk) => {
			data += chunk;
			console.log("response");
		});

		resp.on('end',()=>{
			console.log('mydata');
			console.log(data);
			fs.writeFile(filename, data, function (err) {
				if (err) throw err;
				console.log('Se guardo respuesta de api');
			}); 
			var jsonstr = xmlParser.toJson(data);
			var jsonOb 	= JSON.parse(jsonstr);
			var newEqu = jsonOb.queryresult.pod[1].subpod.plaintext;
			newEqu = newEqu.replace(/ /g, "");
			newEqu = newEqu.split('=');
			if(newEqu[1].search("and")>0){
				newEqu = newEqu[1].split('and');
				return newEqu[0];
			}else{
				return newEqu[1];
			}
		});		
		
		//return newEqu[1];//devuelvo la variable axis despejada para la ecuacion dada

	}).on("error", (err) => {
		console.log("Error: " + err.message);
		return 'ERROR';
	});


}

function getPuntos(nodo_eq, ejes, rz) {
	var expression = '';
	var positive = '';
	var negative = '';
	var minH = -10;
	var maxH = 10;
	var minV = -10;
	var maxV = 10;
	var yval = 0;
	var plot_negative = false;

	var arrayLinealizado = '';
	switch(ejes){
		case 'x-y':
		expression = nodo_eq.eqx;
		expression = expression.replace(/z/g, rz);
		expression = expression.replace(/y/g, "x");
		minH = nodo_eq.xi;
		maxH = nodo_eq.xs;
		minV = nodo_eq.yi;
		maxV = nodo_eq.ys;
		break;

		case 'x-z':
		expression = nodo_eq.eqx;
		expression = expression.replace(/y/g, rz);
		expression = expression.replace(/z/g, "x");
		minH = nodo_eq.xi;
		maxH = nodo_eq.xs;
		minV = nodo_eq.zi;
		maxV = nodo_eq.zs;
		break;

		case 'y-z':
		expression = nodo_eq.eqy;
		expression = expression.replace(/x/g, rz);
		expression = expression.replace(/z/g, "x");
		minH = nodo_eq.zi;
		maxH = nodo_eq.zs;
		minV = nodo_eq.zi;
		maxV = nodo_eq.zs;
		break;

		default:
		break;
	}
	if(expression.indexOf(',')>0){
		expression = expression.split(',');
		positive = math.compile(expression[0])
		negative = math.compile(expression[1]);
		plot_negative = true;
	}else{
		positive = math.compile(expression);
	}
	const expr = math.compile(expression);
	const exprN = math
	paso = (maxH - minH)/no_puntos;
	unidadx = ancho / (maxH - minH);
	unidady = alto / (maxV - minV );

    var xValues = math.range(minH, maxH, paso).toArray()
    var yValues = xValues.map(function (xval) {
     	yval =  positive.evaluate({x: xval});
     	if(typeof yval == 'object'){
	     		yval = 'x';
     	}else{
	     	yval = yval>maxV?'x':yval;
	     	yval = yval<minV?'x':yval;
     	}
        return yval;

    });

    if(plot_negative){
    	console.log('Ploting negative...')
	    var yNeVal = xValues.map(function (xval) {
	     	yval =  negative.evaluate({x: xval});
	     	if(typeof yval == 'object'){
	     		yval = 'x';
	     	}else{
		     	yval = yval>maxV?'x':yval;
		     	yval = yval<minV?'x':yval;
	     	}
	        return yval;
	    });

	    xValues = xValues.concat(xValues); 
	    yValues = yValues.concat(yNeVal); 

    }

    const trace1 = {
        x: xValues,
        y: yValues,
        equation: expression
    }

     Axis(minH, maxH, minV, maxV);
     console.log(expression);
    //arrayLinealizado = Axis(minH, maxH, minV, maxV);
    //arrayLinealizado += ';';
    arrayLinealizado += linealizar(xValues, yValues);


    return arrayLinealizado;
}

/*
  			 |
  			 |
  			 |
  			 |
  			 |
  			 |
  			 |
  			 |
  		320 _|_________________________________
  			 |
			0
*/
function Axis(minH, maxH, minV, maxV){

	var paintaxis = '';
	if(maxH < 0){//si el eje horizontal se muestra en el cuadrante negativo
		axisV = ancho;
	}else if(minH < 0 && maxH >0){//significa que el eje vertical no va en 0, sino va movido
		axisV = (0- minH) * unidadx;//en que pixel 
		axisV = Math.round( axisV );
	}

	if(maxV < 0){
		axisH =  0;
	}else if(minV <0 && maxV >0){
		axisH = alto -((0-minV)*unidady);
		axisH = Math.round(axisH);
	}

	//eje horizontal
	for (var i = 0 ; i < ancho; i++) {
		//formula = y *ancho + x
		// y = axisH
		// x = i
		//paintaxis += i + ','+axisH+';';
		if(i>0){
			paintaxis += ',';
		}
		paintaxis += axisH * ancho + i ;
	}

	//eje vertical
	for (var i = 0; i < alto; i++) {
		//paintaxis += axisV + ','+i+';';
		if(i>0){
			paintaxis += ',';
		}
		paintaxis += i * ancho +axisV ;
		
	}

	return paintaxis;

}


function linealizar(xval,yval) {
	var linea = '';
	var x = 0;
	var y = 0;

	var xlin = [];

	var conteo = 0;
	for (var i = 0; i < xval.length; i++) {
		if(yval[i]!= 'x'){
			conteo ++;
			if(linea != ''){
				linea += ',';
			}
			x = Math.round(axisV + xval[i]*unidadx);
			y = Math.round(axisH + yval[i]*unidady);

			xlin.push([x,y]);
			//utilizar la linea de abajo para tener el resultado linealizado
			linea += y * ancho + x

			//descomentar esto para coordenadas x y
			/*linea += Math.round(axisV + xval[i]*unidadx);
			linea +=',';
			linea += Math.round(axisH + yval[i]*unidady);*/
			
		}
	}

	var lll = {
		x: xval,
		y: yval
	}
	//console.log('PUNTOS');
	console.log(lll);
	console.log(xlin);
	//console.log(xval.length);
	//console.log(conteo);
	return linea;
}

function analizarEcuacion(ecuacion) {
}


function get3DPoints(argument) {
	// body...
}

/*
	reconocer las ecuaciones 

*/
// dejar esto de ultimo para que no se pierda
http.createServer(app).listen(process.env.PORT || 8000, '0.0.0.0');

