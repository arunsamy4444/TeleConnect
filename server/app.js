const express = require("express");
const cors = require("cors");
const dotenv = require("dotenv");
const messageRoutes = require("./routes/messageRoutes");

dotenv.config();

const app = express();

const allowedOrigins = ["https://tele-connect.vercel.app"];

app.use(
  cors({
    origin: function (origin, callback) {
      if (!origin) return callback(null, true); // allow Postman, etc
      if (allowedOrigins.indexOf(origin) === -1) {
        return callback(new Error("CORS not allowed"), false);
      }
      return callback(null, true);
    },
    methods: ["GET", "POST", "OPTIONS"], // explicitly allow OPTIONS
    allowedHeaders: ["Content-Type", "Authorization"], // allow headers you use
  })
);

// This ensures preflight requests are handled
app.options("*", cors());

app.use(express.json());
app.use("/api/message", messageRoutes);

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log(`✅ Server running on port ${PORT}`));
