import React from 'react';
import io from 'socket.io-client';
import './App.css';

const socket = io.connect('http://localhost:5000');

function App() {
  const [messages, setMessages] = React.useState([]);
  const [message, setMessage] = React.useState('');

  React.useEffect(() => {
    getMessages();
  }, []);

  const getMessages = () => {
    socket.on("message", msg => {
      setMessages(old => [...old, msg.morse]);
      setMessage(old => old + msg.text);
    });
    socket.emit("message");
  }

  return (
    <div className="App">
      <div className="Message">
        <p>{message}</p>
      </div>
      <div>
        <p>{messages}</p>
      </div>
    </div>
  );
}

export default App;
