var serial;          // variable to hold an instance of the serialport library
var portName = '/dev/tty.usbmodem14101'; // fill in your serial port name here
var inData;                            // for incoming serial data
var outByte = 0;                       // for outgoing data



////////ml5//////////////////

let mobilenet;
let video;
let label = '';
let num;

////////////perlin//////////
let inc = 0.1;
let scl = 17;
let cols, rows;

let zoff = 0;

let myFont;
function preload() {
  myFont = loadFont('ok.otf');
}

///////////////ml5///////////

function modelReady() {
  console.log('Model is ready!!!');
  mobilenet.predict(gotResults);
}

function gotResults(error, results) {
  if (error) {
    console.error(error);
  } else {
 
    //console.log(results);
    num = results[0].probability;
    //print(num*100);
    label = results[0].className;
    //delay(500);
    mobilenet.predict(gotResults);
  }
}

////////////////////////////////////////


function setup() {
  createCanvas(640, 480);
  cols = floor(width/scl);
  rows = floor(height/scl);
  
  
  
  //serial///
  
   serial = new p5.SerialPort();    // make a new instance of the serialport library
 serial.on('data', serialEvent);  // callback for when new data arrives
 serial.on('error', serialError); // callback for errors
 serial.open(portName);           // open a serial port
  
  
  /////
  
    video = createCapture(VIDEO);
  video.hide();
  background(0);  mobilenet = ml5.imageClassifier('MobileNet', video, modelReady);
  
}


function serialEvent() {
 // read a byte from the serial port:
 var inByte = serial.read();
 // store it in a global variable:
 inData = inByte;
  //outByte = int(results[0].probability);
  //serial.write(outByte);
  
}
 
function serialError(err) {
  println('Something went wrong with the serial port. ' + err);
}


function draw() {
  
  
  //serial.write(outByte);


////////////text/////////////////
  
  background(0, 30);
   textFont(myFont);
    fill(255);
  textSize(12);
  let i;
  let aba = 180*num;
  i=aba;
  text(label, 10, 10+i);
  text(num, width-180, height-i);
  
///////////////////perlin//////////////////////
  
  let yoff = 0;
  for (let y = 0; y<rows; y++){
    let xoff = 0;
    for(let x = 0; x<cols; x++){
      let index = ( x + y * width)*4;
      //let aha = map(num, 0, 1, 0, 0.2);
      let angle = noise(xoff, yoff, zoff)*TWO_PI;
      let v =p5.Vector.fromAngle(angle);
      //push();
     // smooth(0.999999);
      xoff += inc;
      //pop();
      //stroke(0);
      push();
      translate(x*scl, y*scl);
      rotate(v.heading());
      // let aha = map(num, 0, 1, 0, 400);
      //let aha = map(num, 0, 1, 0, 400);
      //print (aha);
      stroke (200*num, 255-400*num, num*400*1.4, num*400);
      //stroke (255, 255, 255);
      strokeWeight(0.001);
      line(0, 0, width/8, width/8);
    
      pop();
      
      // fill(r);
      // rect(x*scl, y *scl, scl, scl);
    }
    yoff+= inc;
    //let ff = map(num, 0, 1, 0.001, 0.007);
    zoff += 0.001;
    //print(ff);
  }


}


function mouseDragged() {
 // map the mouseY to a range from 0 to 255:
 outByte = int(map(mouseY, 0, height, 0, 255));
 // send it out the serial port:
 serial.write(outByte);
}