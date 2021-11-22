var ss = SpreadsheetApp.openById('1BJyN4BL0ocO0awtoRy_8SG9rNVxUKpdmmVezN5DgIXU');
var sheet = ss.getSheetByName('DataLogger');


function doGet(e){
  //----------------------------------------------------------------------------------
  //write_google_sheet() function in esp32 sketch, is send data to this code block
  //----------------------------------------------------------------------------------
  //get gps data from ESP32
  if (e.parameter == 'undefined') {
    return ContentService.createTextOutput("Received data is undefined");
  }

  //----------------------------------------------------------------------------------
  var dateTime = new Date();
  // let time = dateTime.getTime();
  motion = e.parameters.motion;
  moist = e.parameters.moist;

  //----------------------------------------------------------------------------------
  var nextRow = sheet.getLastRow() + 1;

  sheet.getRange("A" + nextRow).setValue(nextRow -1); // ID
  sheet.getRange("B" + nextRow).setValue(dateTime); // Date
  // sheet.getRange("C" + nextRow).setValue(time); // Time
  sheet.getRange("C" + nextRow).setValue(motion); // tag
  sheet.getRange("D" + nextRow).setValue(moist); // value
  //----------------------------------------------------------------------------------

  //returns response back to ESP32
  return ContentService.createTextOutput("Status Updated in Google Sheet");
  //----------------------------------------------------------------------------------
}





//Extra Function. Not used in this project.
//planning to use in future projects.
//this function is used to handle POST request
function doPost(e) {
  var val = e.parameter.value;
  
  if (e.parameter.value !== undefined){
    var range = sheet.getRange('A2');
    range.setValue(val);
  }
}