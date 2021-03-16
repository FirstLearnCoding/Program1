<!DOCTYPE html>
<html>
<head>
	<title>SimplePaintApp</title>
	<style type="text/css">
		#myCanvas{
			padding: 0;
			margin-left: auto;
			margin-right: auto;
			border: 1px solid #000000;
			position: 
			
		}
		body{
			font-family: Arial, Helvetica, sans-serif;
		}
		header{
			padding: 10;
			text-align: center;
			height: 50;
			font-size: 20;
			color: black;
		}
		section{
			text-align: center;
		}
		footer{
			margin: auto;
			padding: 0;
			display: block;
			text-align: center;
			width: 100;
		}
	</style>
</head>
<body>
	<header><b>Simple Paint App</b></header>
	<section>
		<canvas id="myCanvas" height="500" width="1000">my canvas</canvas>
	</section>
	
	<script type="text/javascript">
		var myPics=document.getElementById('myCanvas');
		var context= myPics.getContext('2d');
		var objCount=0;
		var color;
		var canvasx=0;
		var canvasy=0;
		var indicate=false;
		var rectArray=[];
		var x=0;
		var y=0;
		var width;
		var height;
		var i=0;
		var imgData;
		var indicate2=false;
		var deleteRect=0;
		var mousex;
		var mousey;
		var isDrag=false;
		var posx;
		var posy;
		var isMove=false;
		var selectedRect=0;
		

		function clearCanvas(){
			var canvas = document.getElementById('myCanvas'),
        	ctx = canvas.getContext("2d");
    		ctx.clearRect(0, 0, canvas.width, canvas.height);
    		rectArray.length=0;
    		objCount=0;

		}

		myPics.addEventListener('mousedown', function(event){
			var rRect=myPics.getBoundingClientRect();
			var cpox=event.clientX-rRect.left;
			var cpoy=event.clientY-rRect.top;
			var cx=event.clientX;
			var cy=event.clientY;
			rectMove(cpox,cpoy,cx,cy);
			
			
			if(isDrag){
				canvasx=event.offsetX;
				canvasy=event.offsetY;
				getData();
			
				color='rgb(' + Math.floor((Math.random() *254)) + ', ' +
                      Math.floor((Math.random() * 255)) + ', '+ Math.floor((Math.random()*255))+')';
				indicate=true;
			}
			
			


		});
		function rectMove(cpox,cpoy,cx,cy){
			var isThisRect=false;
			if(objCount==0){
				isDrag=true;
			}else {
				for(j=0;j<rectArray.length;j++){
					if(isRectSelected(cpox,cpoy,rectArray[j])){
						selectedRect=j;
						isMove=true;
						isDrag=false;
						isThisRect=true;
					}else{
						isDrag=true;
					}
					if(isThisRect){
						rectArray.push(rectArray.splice(selectedRect,1)[0]);
						isThisRect=false;
						posx=cx-rectArray[objCount-1].x;
						posy=cy-rectArray[objCount-1].y;
					}
				}
			}

		}
		myPics.addEventListener('mousemove', e=>{
			if(indicate){
				putData();
				x=e.offsetX;
				y=e.offsetY;
				width=x-canvasx;
				height=y-canvasy;
				drawRect();
				indicate2=true;

			}else if(isMove){
				
				rectArray[objCount-1].x=e.clientX-posx;
				rectArray[objCount-1].y=e.clientY-posy;
				drawRectangles();
			}
		});
		myPics.addEventListener('mouseup', e=>{

			indicate=false;
			isMove=false;
			isDrag=false;
			sample();
            drawRectangles();

            
		});
		myPics.addEventListener('dblclick', e=>{
			var m;
			var rRect=myPics.getBoundingClientRect();
			mousex=e.clientX-rRect.left; 
			mousey=e.clientY-rRect.top;
			var del=false;
			for(i=0;i<rectArray.length;i++){
				
				if(isRectSelected(mousex,mousey,rectArray[i])){
					deleteRect=i;
					del=true;
				}	
			}
			if(del){
				rectArray.splice(deleteRect, 1);
				objCount=objCount-1;
				del=false;
			}
			drawRectangles();
		});
		function sample(){
			if(indicate2){
				data={x:canvasx,y:canvasy,x1:width,y1:height, paint:color};
				objCount=objCount+1;
				rectArray.push(data);
            	indicate2=false;
			}
		}
		function drawRectangles(){
			var j;
			var canvas = document.getElementById('myCanvas'),
        	ctx = canvas.getContext("2d");
    		ctx.clearRect(0, 0, canvas.width, canvas.height);
			for(j=0;j<rectArray.length;j++){
				var temp=rectArray[j];
				context.beginPath();
				context.strokeStyle="black";
				context.lineWidth=1;
				context.fillStyle=temp["paint"];
				context.fillRect(temp["x"], temp["y"], temp["x1"], temp["y1"]);
				context.stroke();
				context.closePath();
			}
		}
		function isRectSelected(xmouse, ymouse, handle){
			if(xmouse<handle.x||ymouse<handle.y||xmouse>handle.x+handle.x1||ymouse>handle.y+handle.y1){
				return false
			}else{
				return true;
			}
		}
		function getData(){
			imgData=context.getImageData(0,0,myPics.width,myPics.height)
		}
		function putData(){
			context.putImageData(imgData,0,0)
		}
		function drawRect(){
			
			context.beginPath();
			context.strokeStyle='black';
			context.lineWidth=1;
			context.fillStyle=color;
			context.fillRect(canvasx, canvasy, width, height);
			context.stroke();
			context.closePath();
		}	
	</script>
    <footer>
		<button type="button" onclick="clearCanvas()">Clear</button>
		<p id='demo'></p>
	</footer>
</body>
</html>