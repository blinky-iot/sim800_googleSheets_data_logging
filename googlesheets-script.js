
var spreadsheetId = SpreadsheetApp.openById("1v-_PdFnkY7R5TKFmVboEuaFvexIxk8vtSzg4Cy5Rr2o");
var sheet = spreadsheetId.getSheetByName("DHT");
var timezone = "Africa/Nairobi";


function doGet(e) {
  return postData(e);
}

function doPost(e) {
  return postData(e);
}

function postData(e) {
  Logger.log(JSON.stringify(e));

  // Basic error check
  if (!e.parameter.temp || !e.parameter.hum) {
    return ContentService.createTextOutput("Missing parameters");
  }

  var date = new Date();
  var time = Utilities.formatDate(date, timezone, "HH:mm:ss");

  var temp = stripQuotes(e.parameter.temp);
  var hum = stripQuotes(e.parameter.hum);

  var row = [date, time, temp, hum];
  sheet.appendRow(row);

  return ContentService.createTextOutput("Data Sent to Sheets!");
}

function stripQuotes(value) {
  return value.toString().replace(/^["']|["']$/g, "");
}


function getData(e) {
  return postData(e); 
}

