// server/routes/messageRoutes.js
const express = require("express");
const { spawn } = require("child_process");
const path = require("path");

const router = express.Router();

router.post("/", (req, res) => {
  const { name, msg } = req.body;

  // Full path to C++ executable
  const botPath = path.join(__dirname, "../../TeleConnectBackend/telegram_bot.exe");

  // Encode the message for URL
  const fullMsg = encodeURIComponent(`${name}: ${msg}`);

  const child = spawn(botPath, [fullMsg]);

  let output = "";
  let errorOutput = "";

  child.stdout.on("data", (data) => {
    output += data.toString();
  });

  child.stderr.on("data", (data) => {
    errorOutput += data.toString();
  });

  child.on("close", (code) => {
    if (code === 0) {
      res.json({ success: true, result: output });
    } else {
      console.error(errorOutput);
      res.status(500).json({ success: false, error: errorOutput });
    }
  });
});

module.exports = router;
