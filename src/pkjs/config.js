module.exports = [
  {
    "type": "heading",
    "defaultValue": "App Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Please configure the app! :D"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "color",
        "messageKey": "BackgroundColor",
        "defaultValue": "0x000000",
        "label": "Background Color"
      },
      {
        "type": "color",
        "messageKey": "TextColor",
        "defaultValue": "0xFFFFFF",
        "label": "Text Color"
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Times"
      },
      {
        "type": "text",
          "defaultValue": "Times should be in the format 8:30 am"
      },
      {
        "type": "input",
        "messageKey": "StartTime",
        "label": "Start time of work",
        "defaultValue": "8:00 am"
      },
      {
        "type": "input",
        "messageKey": "EndTime",
        "label": "End time of work",
        "defaultValue": "5:00 pm"
      },
      {
        "type": "input",
        "messageKey": "LunchStart",
        "label": "Start time of lunch",
        "defaultValue": "12:00 pm"
      },
      {
        "type": "input",
        "messageKey": "LunchEnd",
        "label": "End time of lunch",
        "defaultValue": "12:30 pm"
      }        
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Misc"
      },
      {
        "type": "text",
          "defaultValue": "Other settings"
      },
      {
        "type": "input",
        "messageKey": "HourlyRate",
        "label": "Hourly Pay Rate (format is 12.00)",
        "defaultValue": "12.00"
      },
      {
        "type": "input",
        "messageKey": "Name",
        "label": "What's your name?",
        "defaultValue": "Captain"
      },
      {
        "type": "input",
        "messageKey": "Seconds",
        "label": "Would you like to see seconds?",
        "defaultValue": true
      },
      {
        "type": "input",
        "messageKey": "DecimalPlaces",
        "label": "How many decimal places do you want to see? (0-3)",
        "defaultValue": "3"
      }        
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];