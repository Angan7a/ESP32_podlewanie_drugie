#include"http.hpp"

String load_page()
{
  //the HTML of the web page
	String page = "";
 page = "<!DOCTYPE HTML>";
 page += "<html>";
 page += "<style>";
 page += "ul {column-count: 3; column-gap: 18rem;}";
 page += "</style>";

page += "<body>";

page += "<p><b>Ustawienia czasu podlewania:</b></p>";
page += "<ul class=\"checkboxes\">";
page += "<form action=\"/act\" method=\"get\">";
page += "<li><label><input type=\"checkbox\" name=\"text24\" value=\"24\" />0:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text1\" value=\"1\" />1:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text2\" value=\"2\" />2:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text3\" value=\"3\" />3:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text4\" value=\"4\" />4:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text5\" value=\"5\" />5:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text6\" value=\"6\" />6:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text7\" value=\"7\" />7:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text8\" value=\"8\" />8:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text9\" value=\"9\" />9:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text10\" value=\"10\" />10:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text11\" value=\"11\" />11:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text12\" value=\"12\" />12:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text13\" value=\"13\" />13:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text14\" value=\"14\" />14:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text15\" value=\"15\" />15:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text16\" value=\"16\" />16:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text17\" value=\"17\" />17:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text18\" value=\"18\" />18:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text19\" value=\"19\" />19:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text20\" value=\"20\" />20:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text21\" value=\"21\" />21:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text22\" value=\"22\" />22:00</label></li>";
page += "<li><label><input type=\"checkbox\" name=\"text23\" value=\"23\" />23:00</label></li>";
page += "</ul>";

page += "<p>Czas podlewania";
page += "<select name=\"czas\">";
page += "<option>10s</option>";
page += "<option>20s</option>";
page += "<option selected>30s</option>";
page += "<option>40s</option>";
page += "<option>50s</option>";
page += "<option>60s</option>";
page += "</select>";
page += "</p>";

page += "<p><input type=\"submit\" value=\"Submit\"></p>";
//page += "<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>";
page +=  "<p></br> </p>";
page += "<p><b>Ustawione parametry podlewania:</b></p>";

int n_line = EEPROM.read(380);
for (int i = 0; i < n_line; i++)
{
    int z1 = EEPROM.read(350 + i);
//    if (z != 100)
    {
        page += "<p>Godzina podlewania: ";
        page += z1;
        page += ":00</p>";
    }
}
    page +=  "<p>Czas podlewania: ";
    int z1 = EEPROM.read(0);
    page += z1;

    page += " sekund</p>";
    page +=  "<p></br></p>";
    page += "</form>";
    page += "<form action=\"/res\" method=\"get\">";
    page += "<p><a class=\"button\" href=\"res\"><button>Restart</button></a>";
    page += "<p><b>Kiedy podlewano:</b></p>";
    int print_line = EEPROM.read(299);
    for (int e = 0; e < 10; e++)
{
             page += EEPROM.read(20*e);
}
page += "</body>";
page += "<\/html>";

return page;
}
