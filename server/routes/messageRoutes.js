const express = require("express");
const { sendMessage } = require("../controllers/messageController");

const router = express.Router();

router.post("/", sendMessage); // <-- POST to "/api/message"

module.exports = router;
