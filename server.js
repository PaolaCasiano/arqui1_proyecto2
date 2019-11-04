var express = require('express')
var http = require('http')
var app = express()
var ListaEcuaciones = require('./listanode')
var ListaLetras = require('./listaLet')
//ESTADOS
//1 ESCRITORIO
//2 MOVIL

var lista = new ListaEcuaciones()
var letras =  new ListaLetras()
var estado = 1

app.post('/guardar_funcion', function (req, res) {
	postB = req.body;
	lista.addEcuacion(posB.equ, posB.xi, posB.xs, posB.yi, posB.ys, posB.zi, posB.zs);	
 });

 app.post('/guardar_letras', function(req,res){
	postB = req.body;
	letras.addLetras(posB.letras);
 });

 app.get('/cambiar_movil', function(req,res){
	estado = 2;
	res.send(2);
 });

 app.get('/get_estado', function(req,res){
	res.send(estado);
 });

 app.get('/cambiar_escritorio', function(req, res){
	estado = 1;
	res.send(1);
 });

app.get('/getUltimaEcuacion', (req, res) => {	
	var codigo = 0;
	var mensaje = '';
	if(estado ==1 ){
		
	}else{

	}
  	res.send(nueval.prueba());
})

app.get('/getUltimoLetrero', (req, res) => {
	var codigo = 0;
	var mensaje = '';
	if(estado ==2){
		
	}else{
		mensaje = 'Modo movil solo puede enviar letras';
		codigo =1;
	}
})


http.createServer(app).listen(8001, () => {
  	console.log('Server started at http://localhost:8001');
});

