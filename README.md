# 📡 Google Sheets Logger with Apps Script (GET Method)
This is a guide on logging data to google sheets using Both WiFi and GPRS - SIM800L
---

## 🛠 Step 1: Set Up Google Apps Script

1. Open your **Google Sheet**.
2. Go to `Extensions > Apps Script`.
3. Delete any default code and paste the following:

```javascript
function doGet(e) {
  const sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Sheet1");

  const temp = e.parameter.temp;
  const hum = e.parameter.hum;
  const timestamp = new Date();

  sheet.appendRow([timestamp, temp, hum]);

  return ContentService.createTextOutput("Data logged successfully");
}
