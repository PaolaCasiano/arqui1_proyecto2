var express = require('express')
var http = require('http')
const https = require('https');
var app = express()
var ListaEcuaciones = require('./listanode')
var ListaLetras = require('./listaLet')
let xmlParser = require('xml2json')
var fs = require('fs');
//ESTADOS
//1 ESCRITORIO
//2 MOVIL

//api link http://api.wolframalpha.com/v2/query?input=solve+3x-7%3D11for+x&appid=LVALQJ-UPG9XXATRG
//http://api.wolframalpha.com/v2/query?input=solve+{{ecuacion lado 1}}%3D{{ecuacion igual a}}for+{{Variable a despejar}}&appid=LVALQJ-UPG9XXATRG

var lista = new ListaEcuaciones()
var letras =  new ListaLetras()
var estado = 1


app.post('/guardar_funcion', function (req, res) {
	var posB = req.body;
	var equation = posB.equ;
	equation = equation.replace(/ /g, "");
	var eqx = getEqAxis(equation, 'x');
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
				);	
 });

 app.post('/guardar_letras', function(req,res){
	postB = req.body;
	letras.addLetras(posB.letras);
 });

 app.get('/cambiar_movil', function(req,res){
	estado = 2;
	res.send(2);
 });

 app.get('/imprimir', function(req,res){
	var str = imprimirListas();
	res.send(str);
 });

 app.get('/', function(req,res){
	let data = '';
	data = letras.returnxml();
	var jsonstr = xmlParser.toJson(data);
	var json = JSON.parse(jsonstr);
	res.send(json.queryresult.pod[1].subpod.plaintext);
 });

 app.get('/get_estado', function(req,res){
	res.send(estado);
 });

 app.get('/cambiar_escritorio', function(req, res){
	estado = 1;
	res.send(1);
 });

 app.get('/prueba',function(req, res){
	var posB = {
		'equ':'(x^2/4) + (y^2/8+2) + z^2 = 2^2 * 1'
		, 'xi': '-10'
		, 'xs': '10'
		, 'yi': '-10'
		, 'ys': '10'
		, 'zi': '-10'
		, 'zs': '10'
	};
	
	var equation = posB.equ;
	equation = equation.replace(/ /g, "");
	//res.send(equation);
	//return;
	var eqx = getEqAxis(equation, 'x');
	var eqy = '';//getEqAxis(equation, 'y');
	var eqz = '';//getEqAxis(equation, 'z');
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
				);	
	var imprime = imprimirListas();
	res.send(imprime);
 });

app.get('/getUltimaEcuacion', (req, res) => {	
	var codigo = 0;
	var mensaje = '';
	var eq = null;
	if(estado ==1 ){
		eq = lista.actual.getPuntos();
		if(lista.actual.siguiente != null){
			lista.moveActual();
		}
	}else{
		codigo = 1;
		mensaje = 'Modo movil solo puede devolver letras'
	}

	var response = {
		'codigo': codigo
		, 'mensaje':mensaje
		, 'puntos': eq
	};
  	res.send(JSON.stringify(response));
})

app.get('/getUltimoLetrero', (req, res) => {
	var codigo = 0;
	var mensaje = '';
	var eq = null;
	if(estado ==2){
		eq = letras.actual.getLetras();
		if(lista.actual.siguiente != null){
			letras.moveActual();
		}
	}else{
		mensaje = 'Modo escritorio solo puede enviar ecuaciones';
		codigo =1;
	}
	var response = {
		'codigo': codigo
		, 'mensaje':mensaje
		, 'puntos': eq
	};
  	res.send(JSON.stringify(response));
});

function imprimirListas(){
	var str = lista.imprimir();
	str += '  \n <br>';
	str += letras.imprimir();
	return str;
}

function getEqAxis(eq, axis){
	var ecuacion = eq;
	ecuacion = ecuacion.replace(/ /g, "");
	ecuacion = ecuacion.split('=');
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


http.createServer(app).listen(8001, () => {
  	console.log('Server started at http://localhost:8001');
});

