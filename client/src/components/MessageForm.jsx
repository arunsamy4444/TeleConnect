import { useState } from "react";
import "../styles/MessageForm.css";

export default function MessageForm() {
  const [name, setName] = useState("");
  const [msg, setMsg] = useState("");
  const [status, setStatus] = useState("");

  const handleSubmit = async (e) => {
    e.preventDefault();
    setStatus("Sending...");

    try {
// frontend/src/MessageForm.jsx
const res = await fetch(`${process.env.REACT_APP_API_URL}/api/message`, {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ name, msg }),
});



      const data = await res.json();

      if (data.success) {
        setStatus("Message sent successfully!");
        setName("");
        setMsg("");
      } else {
        setStatus("Failed to send message.");
      }
    } catch (err) {
      setStatus("Error sending message.");
      console.error(err);
    }
  };

  const getStatusClass = () => {
    if (status === "Sending...") return "status-sending";
    if (status === "Message sent successfully!") return "status-success";
    if (status.includes("Error") || status.includes("Failed")) return "status-error";
    return "";
  };

  return (
    <div className="message-form-container">
      <div className="message-form-wrapper">
        <h2 className="message-form-title">TELE CONNECT </h2>
        <form onSubmit={handleSubmit} className="winter-form">
          <div className="form-group">
            <input
              type="text"
              className="form-input"
              placeholder=" "
              value={name}
              onChange={(e) => setName(e.target.value)}
              required
            />
            <label className="form-label">Your Name</label>
          </div>
          
          <div className="form-group">
            <textarea
              className="form-textarea"
              placeholder=" "
              value={msg}
              onChange={(e) => setMsg(e.target.value)}
              required
            ></textarea>
            <label className="form-label">Your Message</label>
          </div>
          
          <button 
            type="submit" 
            className={`winter-button ${status === "Sending..." ? "sending" : ""}`}
            disabled={status === "Sending..."}
          >
            {status === "Sending..." ? "Sending..." : "Send Message"}
          </button>
        </form>
        
        {status && (
          <div className={`status-message ${getStatusClass()}`}>
            {status}
          </div>
        )}
      </div>
    </div>
  );
}