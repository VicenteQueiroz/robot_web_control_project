import logo from './logo.svg';
import './App.css';

import { RobotControlClient, CommandRequest, CommandResponse } from './proto/robot_grpc_web_pb';
import { SendCommand } from './proto/robot_pb';

const sendToServer = async msg => {
  console.log("Sending to server!")
  const EnvoyURL = "http://localhost:8000";
  const client = new RobotControlClient(EnvoyURL);
  const request = new CommandRequest();
  request.setCommand(msg);

  await client.sendCommand(request, {}, (err, response) => {
    if (err) {
      console.error(err);
    } else {
      console.log("Got response from the server: ", response.getMessage());
    }
  });
};

function App() {

  const onClickButton = (msg) => {
    sendToServer(msg);
  };

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <button onClick={() => onClickButton("MOVE_UP")}>Move Left</button>
        <button onClick={() => onClickButton("MOVE_DOWN")}>Move Right</button>
      </header>
    </div>
  );
}

export default App;
