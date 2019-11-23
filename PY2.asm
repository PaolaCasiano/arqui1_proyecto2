setVideoMode macro 
  mov ah,0Fh
  int 10h
  mov saveMode,al

  mov ah,0
  mov al,Modo_13
  int 10h

    mov cx, SEGMENTO_VIDEO 
    push cx 
  pop es

endm

setOriginalMode macro
  mov ah,0 
  mov al,saveMode
  int 10h

endm

draw macro poslin, color
    push dx

    mov di,poslin
    mov dl,color
    mov es:[di],dl

    pop dx

endm

graficarCadena macro cadena,num
LOCAL PrimerNum,Coma,SalirNum,PrimerCoordenada,ComaCoordenada1,SegundaCoordenada,PuntoComa1,TerceraCoordenada,ComaCoordenada3,CuartaCoordenada,Dolar,GraficarEjeX,GraficarEjeY,Salir
xor si,si
xor di,di
num1dw dw ?
;COORDENADAS--------------
superiorX dw ?
inferiorX dw ?
superiorY dw ?
inferiorY dw ?
mov superiorX,0
mov superiorY,0
mov inferiorX,0
mov inferiorY,0
;GRAFICA------------------
digitnum dw ?
ls dw ?
mov ls,0
mov digitnum,0
PrimerNum:
mov al,cadena[si]
cmp al,2ch
je Coma
cmp al,3bh ;ANTES "$" AHORA ";"
je SalirNum ;ANTES Salir
mov num[di],al
inc di
inc si
inc digitnum
inc ls
jmp PrimerNum 
Coma:
dec ls
stringANumero digitnum,ls,num
mov num1dw,bx
draw num1dw,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0
mov al,cadena[si]
cmp al,3bh  ;ANTES "$" AHORA ";"
je SalirNum 
jmp PrimerNum
SalirNum:
dec ls
stringANumero digitnum,ls,num
mov num1dw,bx
draw num1dw,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0

jmp PrimerCoordenada
;-----------------------------------------< EMPIEZAN COORDENADAS
PrimerCoordenada:
; SE PASA A HEXADECIMAL EL PRIMER NUMERO
mov al,cadena[si]
cmp al,2ch
je ComaCoordenada1
;cmp al,24h 
;je Salir ;ANTES Salir
mov num[di],al
inc di
inc si
inc digitnum
inc ls
jmp PrimerCoordenada 
ComaCoordenada1:
;-----------------------------------------< SE CONVIERTE A HEX EL INFERIOR DE X
dec ls
stringANumero digitnum,ls,num
mov inferiorX,bx
;draw inferiorX,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0
;mov al,cadena[si]
;cmp al,24h
;je Salir ;ANTES "$" AHORA ";"
jmp SegundaCoordenada
SegundaCoordenada:
mov al,cadena[si]
cmp al,3bh
je PuntoComa1
;cmp al,24h 
;je Salir ;ANTES Salir
mov num[di],al
inc di
inc si
inc digitnum
inc ls
jmp SegundaCoordenada 
PuntoComa1:
;-----------------------------------------< SE CONVIERTE A HEX EL SUPERIOR DE X
dec ls
stringANumero digitnum,ls,num
mov superiorX,bx
;draw superiorX,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0
;mov al,cadena[si]
;cmp al,24h
;je Salir ;ANTES "$" AHORA ";"
jmp TerceraCoordenada
TerceraCoordenada:
mov al,cadena[si]
cmp al,2ch
je ComaCoordenada3
;cmp al,24h 
;je Salir ;ANTES Salir
mov num[di],al
inc di
inc si
inc digitnum
inc ls
jmp TerceraCoordenada
ComaCoordenada3:
;-----------------------------------------< SE CONVIERTE A HEX EL INFERIOR DE Y
dec ls
stringANumero digitnum,ls,num
mov inferiorY,bx
;draw inferiorY,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0
mov al,cadena[si]
;cmp al,24h
;je Salir ;ANTES "$" AHORA ";"
jmp CuartaCoordenada 
CuartaCoordenada:
mov al,cadena[si]
;cmp al,2ch
;je ComaCoordenada4
cmp al,24h 
je Dolar ;ANTES Salir
mov num[di],al
inc di
inc si
inc digitnum
inc ls
jmp CuartaCoordenada
Dolar:
;-----------------------------------------< SE CONVIERTE A HEX EL SUPERIOR DE Y
dec ls
stringANumero digitnum,ls,num
mov superiorY,bx
;draw superiorY,0Fh
limpiarVariable2 num
inc si
xor di,di
mov digitnum,0
mov ls,0
mov al,cadena[si]
;cmp al,24h
;je Salir ;ANTES "$" AHORA ";"
;jmp GraficarEjeX
mov dl,0Fh
mov di,inferiorX
jmp GraficarEjeX
GraficarEjeX:
mov es:[di],dl
inc di
cmp di,superiorX 
jne GraficarEjeX
mov di,inferiorY
mov cx,0c8h ;198 EN DECIMAL (supY??) NO PUEDEN SER LINEALIZADAS
jmp GraficarEjeY
GraficarEjeY:  
draw2 inferiorY,cx,0Fh  ;160
loop GraficarEjeY 
Salir:

endm

draw2 macro x0, y0, color  
push cx
mov ah, 0ch
mov al, color
mov bh, 0h
mov dx, y0
mov cx, x0
int 10h 
pop cx
endm

DibujarEjes macro infX,supX,infY,supY
LOCAL GraficarEjeX,GraficarEjeY

mov dl,0Fh
mov di,infX
GraficarEjeX:
mov es:[di],dl
inc di
cmp di,supX 
jne GraficarEjeX

;mov di,supY
mov cx,0c8h ;198 EN DECIMAL (supY??) NO PUEDEN SER LINEALIZADAS
GraficarEjeY:  
draw2 infY,cx,0Fh  ;160
loop GraficarEjeY 
endm

stringANumero macro digitos,lsnum,num
  LOCAL repetir
    push si
    
    mov cx,digitos ;(Porque tiene 4 digitos el numero) 
    mov si,lsnum ;(Para que si apunte al digito menos significativo)
    
    mov  bx, 0
    mov  bp, 1
  repetir:         
                    
    mov  al,num[si] 
    sub  al,48 
    mov  ah,0 
    mul  bp 
    add  bx,ax  

    mov  ax,bp
    mov  bp,10
    mul  bp 
    mov  bp, ax   

    dec  si 
  Loop repetir
   
  pop si

endm

print macro buffer
  mov ax, @data
  mov ds,ax
  mov dx, offset buffer
  mov ah,9
  int 21h
endm

leerOpcion macro
  mov ah,0dh
  int 21h
  mov ah,01h
  int 21h
endm

abrirArchivo macro path,handler
  mov ah,3dh
  mov al,02h
  lea dx,path
  int 21h
  jc ErrorAbrir
  mov handler,ax
endm

cerrarArchivo macro handler
  mov ah,3eh
  mov bx,handler
  int 21h
  jc ErrorCerrar
endm

leerArchivo macro handler,bf,bytes
  mov ah,3fh
  mov bx,handler
  mov cx, bytes
  lea dx,bf
  int 21h
  jc ErrorLeer
endm

limpiarVariable macro var,tam,caracter
  LOCAL Loops
  xor si,si
  xor cx,cx
  mov cx,tam
  Loops:
    mov var[si],caracter
    inc si
  Loop Loops
endm

limpiarVariable2 macro var
  LOCAL Loops
    xor di,di
    xor cx,cx
    mov cx, SIZEOF var
  Loops:
    mov var[di],24h
    inc di
  Loop Loops
endm

extraerEcuacion macro xml, var
  LOCAL LoopPrincipal,etEcuacion,etEcuacion2,LeerEcuacion,Salir
    xor si,si
    xor di,di
  LoopPrincipal:
    mov al,xml[si]
    cmp al,65h
    je etEcuacion
    inc si
    jmp LoopPrincipal
  etEcuacion:
    mov al,xml[si]
    cmp al,6eh
    je etEcuacion2
    inc si
    jmp etEcuacion
  etEcuacion2:
    inc si
    jmp etEcuacion3
  etEcuacion3:
    inc si
    jmp LeerEcuacion
  LeerEcuacion:
    mov al,xml[si]
    cmp al,3ch
    je Salir
    mov var[di],al
    inc si
    inc di
    jmp LeerEcuacion
  Salir:

endm

extraerLimites macro xml,var,caracter
  LOCAL LoopPrincipal,etLimites,etLimites2,etLinf,etLinf2,etLinf3,etLinf4,etLinf5,LeerLimites,etSup,etSup2,etSup3,etSup4,LeerLimites2,Salir
    xor si,si
    mov al,3bh
    mov var[di],al
    inc di
  LoopPrincipal:
    mov al,xml[si]
    cmp al,65h
    je etLimites
    inc si
    jmp LoopPrincipal
  etLimites:
    mov al,xml[si]
    cmp al,3eh ; SI ENCUENTRA ">" ANTES QUE "x" ES PORQUE ES ETIQUETA ECUACION
    je LoopPrincipal
    cmp al,caracter ; x, y o z
    je etLimites2
    inc si
    jmp etLimites
  etLimites2:
    inc si
    jmp etLinf2
  etLinf2:
    inc si
    jmp etLinf3
  etLinf3:
    mov al,xml[si]
    cmp al,3eh
    je etLinf4
    inc si
    jmp etLinf3
  etLinf4:
    inc si
    jmp LeerLimites
  LeerLimites:
    mov al,xml[si]
    cmp al,3ch
    je etSup
    mov var[di],al
    inc si
    inc di
    jmp LeerLimites
  etSup:
    mov al,2ch
    mov var[di],al
    inc di
    jmp etSup2
  etSup2:
    mov al,xml[si]
    cmp al,70h
    je etSup3
    inc si
    jmp etSup2
  etSup3:
    inc si
    jmp etSup4
  etSup4:
    inc si
    jmp LeerLimites2
  LeerLimites2:
    mov al,xml[si]
    cmp al,3ch
    je Salir
    mov var[di],al
    inc si
    inc di
    jmp LeerLimites2
  Salir:

endm

enviar macro buffer
  LOCAL send, exit
		;preparamos puerto
		mov ah,00h ; inicializa puerto
		mov al,11100011b ; parámetros
		mov dx,00 ; puerto COM1
		int 14h ; llama al BIOS

		mov si,00h
	
  send:
		mov ah,01h ; peticion para caracter de transmisión
    mov al,buffer[si]; caracter a enviar

		cmp al,24h ; se repite el envio de datos hasta que se llegue al final del arreglo.
    je exit 

    push ax
    push dx

    mov ah,02h
    mov dl,buffer[si]
    int 21h
    
    pop dx
    pop ax 

		mov dx,00 ;puerto COM1
		int 14h ;llama al BIOS

		inc si   ;Incrementamos nuestro contador
		
    jmp send 

  exit:

endm

recibir macro buffer
  LOCAL receive, exit
		; preparamos puerto
		mov ah,00h ; inicializa puerto
		mov al,11100011b ; parámetros
		mov dx,00 ; puerto COM1
		int 14h ; llama al BIOS

		mov si,00h
	
  receive:
    mov al,0h ; reiniciamos al
		mov ah,02h ; petición para recibir caracter
		mov dx,00 ; puerto COM1
		int 14h ; llama al BIOS

		cmp al,24h ; se repite el envio de datos hasta que se llegue al final del arreglo.
    je exit 

    mov buffer[si],al

    push ax
    push dx

    mov ah,02h
    mov dl,buffer[si]
    int 21h
    
    pop dx
    pop ax 

		inc si 
    jmp receive

  exit:
    print msg_point
    
endm

atender macro men
  LOCAL pause, controlperdido, controlretomado, gotoMenu, exit
    ; preparamos puerto
    mov ah,00h ; inicializa puerto
    mov al,11100011b ; parámetros
    mov dx,00 ; puerto COM1
    int 14h ; llama al BIOS

    mov al,0h ; reiniciamos al
    mov ah,02h ; petición para recibir caracter
    mov dx,00 ; puerto COM1
    int 14h ; llama al BIOS

    cmp al,'#'
    je controlperdido  

    jmp exit

  controlperdido:
    print msg_controlp
  
  pause:
    ; config again the port ?

    mov al,0h ; reiniciamos al
	  mov ah,02h ; petición para recibir caracter
	  mov dx,00 ; puerto COM1
	  int 14H ; llama al BIOS

	  cmp al,'#'
    je controlretomado

    jmp pause

  controlretomado:
    print msg_controlr
    push ax
    mov ah,men
    cmp ah,1
    je gotoMenu
    pop ax
    jmp Grafica2D

  gotoMenu:
    pop ax
    jmp Menu

  exit:
    
endm

verificacion1 macro
  LOCAL ini, next, continue
    ini:
			mov ah,01h
			int 16h ; check keyboard buffer
			jz next
			
			mov ah,00h ; read from keyboard buffer
			int 16h
			
      cmp al,31h
      je CargarArchivo

      cmp al,32h
      je Grafica2D
      
      cmp al,33h
      je Grafica3D

      cmp al,34h
      je Salir

		next:
      atender 1

    continue:
      jmp ini
endm 

verificacion2 macro
  LOCAL ini, next, eje_xy, eje_xz, eje_yz, rec, pause, exit
    ini:
			mov ah,01h
			int 16h ; check keyboard buffer
			jz next
			
			mov ah,00h ; read from keyboard buffer
			int 16h
			
      cmp al, 31h
      je eje_xy

      cmp al,32h
      je eje_xz
      
      cmp al,33h
      je eje_yz

      cmp al,34h
      je Menu

		next:
      atender 0
      jmp ini

    eje_xy:
      enviar v1
      jmp rec

    eje_xz:
      enviar v2
      jmp rec

    eje_yz:
      enviar v3
    rec: 
      print msg_load
      limpiarVariable varplot, SIZEOF varplot, 24h
      recibir varplot
      print msg_2D
      
      setVideoMode
      graficarCadena varplot, buffernum
    pause:
      mov ah,01h
			int 16h ; check keyboard buffer
			jz pause

      mov ah,00h ; read from keyboard buffer
			int 16h

      cmp ah,1
			jne pause

    exit: 
      setOriginalMode

    jmp Grafica2D
    
endm 

.model small
.stack 100h
.data

;menu:
menuheader db 0ah,0dh,'-----------MENU PRINCIPAL-----------','$'
opcion1 db 0ah,0dh,'1. Cargar ecucacion','$'
opcion2 db 0ah,0dh,'2. Grafica 2D$','$'
opcion3 db 0ah,0dh,'3. Grafica 3D$','$'
opcion4 db 0ah,0dh,'4. Salir$','$'
ingreseop db 0ah,0dh,'Ingrese opcion: ','$'
saltolinea db 0ah,0dh,' ','$'

;menu 2D:
menu2Dheader db 0ah,0dh,'--------------MENU 2D---------------$','$'
opcion1_2D db 0ah,0dh,'1. Ejes x-y$','$'
opcion2_2D db 0ah,0dh,'2. Ejes x-z$','$'
opcion3_2D db 0ah,0dh,'3. Ejes y-z$','$'
opcion4_2D db 0ah,0dh,'4. Regresar$','$'

;msg:
msg_3D db 0ah,0dh,'Generando grafica 3D...', '$'
msg_2D db 0ah,0dh,'Generando grafica 2D...', '$'
msg_load db 0ah,0dh,'GET POINTS...', '$'
msg_point db 0ah,0dh,'.', '$'
msg_controlp db 0ah,0dh,'Control perdido...', '$'
msg_controlr db 0ah,0dh,'Control retomado...', '$'

;archivo:
path db "ECUACION.TXT", 0
handlertexto dw ?
bufarchivo db 1000 dup('$')

;modo video
saveMode BYTE ?
SEGMENTO_VIDEO = 0A000h
Modo_13 = 13h

;graficar
COLOR = 9
poslineal word 0 ; coordenada linealizada
buffernum db 6 dup ('$')
digitos dw ?

;lexico:
elexico db 0ah,0dh,'************ ERROR LEXICO ************','$'
caracternoesperado db 0ah,0dh,'Caracter no esperado: ','$'
cne db 1 dup ('$')
tpy2 db "py2"
tecuacion db "ecuacion"
tejex db "ejex"
tejey db "ejey"
tejez db "ejez"
tlinf db "linf"
tsup db "lsup"

;errores:
error1 db 0ah,0dh,'************ERROR AL ABRIR ARCHIVO*************','$'
error2 db 0ah,0dh,'************ERROR AL CERRAR ARCHIVO************','$'
error3 db 0ah,0dh,'************ERROR AL LEER ARCHIVO**************','$'

; buffer equation
varecuacion db 100 dup ('$')

; buffer plot
varplot db 5000 dup ('$')

; peticiones
v1 db 'v1','$'
v2 db 'v2','$'
v3 db 'v3','$'
D3 db '3D','$'

.code
main proc
      mov ax, @data
      mov ds,ax 
    Menu:
      print menuheader
      print opcion1
      print opcion2
      print opcion3
      print opcion4
      print ingreseop

      verificacion1

    CargarArchivo:
      limpiarVariable bufarchivo, SIZEOF bufarchivo, 24h
      limpiarVariable varecuacion, SIZEOF varecuacion, 24h

      abrirArchivo path, handlertexto
      leerArchivo handlertexto,bufarchivo,SIZEOF bufarchivo
      cerrarArchivo handlertexto
      
      extraerEcuacion bufarchivo,varecuacion
      extraerLimites bufarchivo,varecuacion,78h
      extraerLimites bufarchivo,varecuacion,79h
      extraerLimites bufarchivo,varecuacion,7ah

      enviar varecuacion
      ;print varecuacion

      jmp Menu
          
    Grafica2D:
      print menu2Dheader
      print opcion1_2D
      print opcion2_2D
      print opcion3_2D
      print opcion4_2D
      print ingreseop
      
      verificacion2

    Grafica3D:
      print msg_3D
      enviar D3
      jmp Menu

    Salir:
      mov ah,4ch
      xor al,al
      int 21h

    ; errores
    ErrorAbrir:
      print saltolinea
      print error1
      jmp Menu

    ErrorCerrar:
      print saltolinea
      print error1
      jmp Menu

    ErrorLeer:
      print saltolinea
      print error3
      jmp Menu

main endp
end main 
