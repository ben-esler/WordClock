String generateResponse(String lastAction = ""){
  DateTime time = rtc.now();
  String curDate = time.timestamp(DateTime::TIMESTAMP_DATE);
  String curTime = time.timestamp(DateTime::TIMESTAMP_TIME);
 
  String response = "";
  response +=  "<!DOCTYPE html>\n"
               "<html>\n"
               "<head>\n"
               "  <title>Word Clock Setup</title>\n"
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
               "    <h3>Current time date</h3>\n"
               "    <form action='/datetime'>\n"
               "      <input type='date' name='date' value='" + curDate + "'>\n"
               "      <input type='time' name='time' value='" + curTime + "'>\n"
               "      <input type='submit' value='Set'>\n"
               "    </form>\n"
               "    <form action='/datetime' onsubmit='return getDeviceTime()'>\n"
               "      <input type='date' name='date' id='date' value='2020-10-31' hidden>\n"
               "      <input type='time' name='time' id='time' value='02:57' hidden>\n"
               "      <input type='submit' value='Sync Device Time to Clock'>\n"
               "    </form>\n"
               ""
               "    <h3>Birthdays</h3>\n";
  if (birthdays[9].year == 0) {      
    response +="    <form action='/birthday_add'>\n"
               "      <input type='date' name='birthday_new'>\n"
               "      <input type='submit' value='add'>\n"
               "    </form>\n";
  }
  for (int i = 0; i < 10; i++) {      
    if (birthdays[i].year != 0) {
      response += "    <form action='/birthday_remove'>\n"
                  "      <input type='text' name='birthday_index' value='" + String(i) + "' hidden>\n"
                  "      <input type='date' name='birthday_date' value='" + dateToString(birthdays[i])  + "' readonly>\n"
                  "      <input type='submit' value='Remove'>\n"
                  "    </form>\n";
    }
  }
  response += "    <h3>Brightness Controls</h3>\n"
              "    <form action='/capture_dim'>\n"
              "      <input type='submit' value='Capture Dim Room'>\n"
              "    </form>\n"
              "    <form action='/capture_bright'>\n"
              "      <input type='submit' value='Capture Bright Room'>\n"
              "    </form>\n"
              "    <form action='/bightness_min'>\n"
              "      Dim Room Brightness: <input type='range' name='bightness_min' min='1' max='767' value='" + (String)brightnessMin + "'>\n"
              "      <input type='submit'>\n"
              "    </form>\n"
              "    <form action='/bightness_max'>\n"
              "      Bright Room Brightness: <input type='range' name='bightness_max' min='1' max='767' value='" + (String)brightnessMax + "'>\n"
              "      <input type='submit'>\n"
              "    </form>\n"
              "    <br>\n"
              "    <br>\n"
              "    <br>\n"
              "    <form action='/end_setup'>\n"
              "      <input type='submit' value='Exit Setup'>\n"
              "    </form>\n"
              "    <p><font color='red'>" + lastAction + "</p>\n"
              "  </center>\n"
              "</body>\n"
              "</html>\n";
  return response;
}
