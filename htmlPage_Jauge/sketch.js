// Declare a "SerialPort" object
var serial;
var latestData = "waiting for data";  // you'll use this to write incoming data to the canvas

var fillRatio = 0;

let img;
let myFont;

function preload() {
  img = loadImage('assets/page-Suivi-sans-jauge.png');
  myFont = loadFont("assets/Syne-Regular.ttf");
}

function setup() {
  createCanvas(1280, 720);

  // Instantiate our SerialPort object
  serial = new p5.SerialPort();

  serial.list();
  // MAC OsX Port
  //serial.open("/dev/cu.usbmodem14111");
  // Ubuntu Port
  serial.open("/dev/ttyACM0");

  // Here are the callbacks that you can register

  // When we connect to the underlying server
  serial.on('connected', serverConnected);
  // When we some data from the serial port
  serial.on('data', gotData);
  // When or if we get an error
  serial.on('error', gotError);
  // When our serial port is opened and ready for read/write
  serial.on('open', gotOpen);

  

}

// We are connected and ready to go
function serverConnected() {
  console.log("Connected to Server");
}

// Connected to our serial device
function gotOpen() {
  console.log("Serial Port is Open");
}

// Ut oh, here is an error, let's log it
function gotError(theerror) {
  console.log(theerror);
}

// There is data available to work with from the serial port
function gotData() {
  var currentString = serial.readLine();  // read the incoming string
  trim(currentString);                    // remove any trailing whitespace
  
  if (!currentString) return;             // if the string is empty, do no more
  if(currentString == "+1"){
    fillRatio++;
    fillRatio %= 100;
    serial.write(str(fillRatio) + '\n');
  
  }
  
  console.log(currentString);             // println the string
  latestData = currentString;            // save it for the draw method
  
}

function draw() {
  
  image(img, 0, 0);
  //textFont(myFont);
  
  //background(255,255,255);
  //text(latestData, 10, 10);
  var jaugeX = 855;
  var jaugeY = 652;
  // Score du quartier ------
  fill('#B9DCBE');
  noStroke();
  var maxRelativeSizeYQuartier = 110;
  var relativeSizeYQuartier = maxRelativeSizeYQuartier * (fillRatio/100);
  rect(jaugeX, jaugeY - 260, 18, 260, 18);
  rect(jaugeX, jaugeY - 250 - relativeSizeYQuartier,18, relativeSizeYQuartier, 18);
  
  fill('black');
  var relativeSizeYQuartierText = jaugeY - 250 - relativeSizeYQuartier + 10* (fillRatio/100);
  rect(jaugeX, relativeSizeYQuartierText, 20, 3);
  textSize(12);
  textAlign(LEFT, CENTER);
  text('Score de mon quartier', jaugeX + 25, relativeSizeYQuartierText, 100, 30);
  
  
  // Score de ma poubelle ------
  fill('#467660');
  noStroke();
  var maxRelativeSizeYMaPoubelle = 360;
  var relativeSizeYMaPoubelle = maxRelativeSizeYMaPoubelle * (fillRatio/100);
  rect(jaugeX,jaugeY - relativeSizeYMaPoubelle,18, relativeSizeYMaPoubelle, 18);
  
  fill('black');
  var relativeSizeYMaPoubelleText = jaugeY - relativeSizeYMaPoubelle + 10* (fillRatio/100);
  rect(jaugeX, relativeSizeYMaPoubelleText, 20, 3);
  textSize(12);
  textAlign(LEFT, CENTER);
  text('Score de ma poubelle', jaugeX + 25, relativeSizeYMaPoubelleText, 100, 30);
  text(str(fillRatio) + " %", jaugeX + 125, relativeSizeYMaPoubelleText + 10);
  
}
