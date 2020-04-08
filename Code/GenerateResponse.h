String generateResponse(String lastAction = ""){
  DateTime time = rtc.now();
  String curDate = time.timestamp(DateTime::TIMESTAMP_DATE);
  String curTime;
  if (time.hour() < 10){curTime += "0";}
  curTime += (String)time.hour() + ":";
  if (time.minute() < 10){curTime += "0";}
  curTime +=(String)time.minute();
 
  String response = "";
  response +=  "<!DOCTYPE html>\n"
               "<html>\n"
               "<head>\n"
               "  <title>Word Clock Setup</title>\n"
               "  <link rel='icon' href='data:,'>\n" //Stops favicon.ico requests
               "  <link rel='stylesheet' type='text/css' href='/styleSheet.min.css'>"
               "  <script>\n"
               "    function getDeviceTime() {\n"
               "      var d = new Date();\n"
               "      document.getElementById('date').value = d.toISOString().split('T')[0];\n"
               "      h = (d.getHours()<10?'0':'') + d.getHours();\n"
               "      m = (d.getMinutes()<10?'0':'') + d.getMinutes();\n"
               "     document.getElementById('time').value = h + ':' + m;\n"
               "    }\n"
               "  </script>\n"
               "</head>\n"
               "<body>\n"
               "  <center>\n"
               "    <h1>Word Clock Setup:</h1>\n"
               "    <form class='setTime'  action='/datetime'>\n"
               "      <input type='date' name='date' value='" + curDate + "'>\n"
               "      <input type='time' name='time' value='" + curTime + "' step='60'>\n"
               "      <input type='submit' value='Set'>\n"
               "    </form>\n"
               "    <form class='findTime' action='/datetime' onsubmit='return getDeviceTime()'>\n"
               "      <input type='date' name='date' id='date' value='2020-10-31' hidden>\n"
               "      <input type='time' name='time' id='time' value='02:57' hidden>\n"
               "      <input type='submit' value='Sync Device Time to Clock'>\n"
               "    </form>\n"
               ""
               "    <h3>Birthdays</h3>\n";
  if (birthdays[9].year == 0) {      
    response +="    <form class='birthday add' action='/birthday_add'>\n"
               "      <input type='date' name='birthday_new'>\n"
               "      <input type='submit' value='add'>\n"
               "    </form>\n";
  }
  for (int i = 0; i < 10; i++) {      
    if (birthdays[i].year != 0) {
      response += "    <form class='birthday remove' action='/birthday_remove'>\n"
                  "      <input type='text' name='birthday_index' value='" + String(i) + "' hidden>\n"
                  "      <input type='date' name='birthday_date' value='" + dateToString(birthdays[i])  + "' readonly>\n"
                  "      <input type='submit' value='Remove'>\n"
                  "    </form>\n";
    }
  }
  response += "    <h3>Brightness Controls</h3>\n"
              "    <form class='capture dim' action='/capture_dim'>\n"
              "      <input type='submit' value='Capture Dim Room'>\n"
              "    </form>\n"
              "    <form class='capture bright' action='/capture_bright'>\n"
              "      <input type='submit' value='Capture Bright Room'>\n"
              "    </form>\n"
              "    <form class='brightness' action='/brightness'>\n"
              "      <div class='multi-range' data-lbound='" + (String)brightnessMin + "' data-ubound='" + (String)brightnessMax + "'>\n"
              "        <input name='brightness_min' type='range' min='1' max='765' step='1' value='" + (String)brightnessMin + "' oninput='this.parentNode.dataset.lbound=this.value;'/>\n"
              "        <input name='brightness_max' type='range'  min='1' max='765' step='1' value='" + (String)brightnessMax + "' oninput='this.parentNode.dataset.ubound=this.value;'/>\n"
              "      </div>\n"
              "      <input value='Set Brightness' type='submit'>\n"
              "    </form>\n"
              "    <br>\n";
  if (lastAction != "") {
    response += "    <p class='log'>" + lastAction + "</p>\n";
  }
  response += "    <br>\n"
              "    <form class='exit' action='/end_setup'>\n"
              "      <input type='submit' value='Exit Setup'>\n"
              "    </form>\n"
              "    <br>\n"
              "  </center>\n"
              "</body>\n"
              "</html>\n";
  return response;
}
