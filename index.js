const express = require('express');
const axios = require('axios');
const app = express();
const PORT = 3000;

// Your Google Apps Script Web App URL
const GOOGLE_SCRIPT_URL = 'https://script.google.com/macros/s/AKfycbwlS5XQkTyxypw53-NIs2_XSIRcqAyM25jzZY_DRH5nEoSYf865HXBC-gotA8G9MNoe-w/exec';

// Middleware GET endpoint
app.get('/post-data', async (req, res) => {
  const { temp, hum } = req.query;

  if (!temp || !hum) {
    return res.status(400).send('Missing temp or hum');
  }

  try {
    // Forward to Google Sheets via GET
    const response = await axios.get(GOOGLE_SCRIPT_URL, {
      params: { temp, hum },
    });

    console.log(`Forwarded → Temp: ${temp}, Hum: ${hum}`);
    res.status(200).send('OK');
  } catch (error) {
    console.error('Forwarding error:', error.message);
    res.status(500).send('Failed to forward data');
  }
});

// Start the server
app.listen(PORT, () => {
  console.log(`Middleware running at: http://localhost:${PORT}/post-data`);
});
