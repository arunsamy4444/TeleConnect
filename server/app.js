const express = require("express");
const cors = require("cors");
const dotenv = require("dotenv");
const messageRoutes = require("./routes/messageRoutes");
dotenv.config();
const app = express();

// Allowed origins (local + deployed frontend)
const allowedOrigins = [
  "http://localhost:3000",              // local React
  "https://tele-connect.vercel.app"     // live React
];

app.use(cors({
  origin: (origin, callback) => {
    if (!origin) return callback(null, true);
    if (allowedOrigins.includes(origin)) return callback(null, true);
    return callback(new Error("Not allowed by CORS"));
  },
  methods: ["GET","POST","OPTIONS"],
  allowedHeaders: ["Content-Type","Authorization"]
}));

app.options("*", cors());
app.use(express.json());
app.use("/api/message", messageRoutes);

const PORT = 5000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
