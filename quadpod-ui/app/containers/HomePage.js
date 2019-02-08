import React from 'react'
import { connect } from 'react-redux'

import Gamepad, { Layouts } from '../components/Gamepad'

import ReconnectingWebSocket from 'reconnecting-websocket'

// Actions
import { updateControllerState, updateConnectionState, updateRobotState } from '../modules/actions'

// Assets
import logo from '../../resources/icons/logo.svg'
import quadpod from '../../resources/icons/quadpod.svg'
import controller from '../../resources/icons/controller.svg'

import { Brand, StyledWrapper, StyledCard, Robot, ProximityMeasurementLabel, ControllerLabel, ConnectivityLabel } from './styled'

class HomePage extends React.Component {
  constructor() {
    super();
    this.state = {
      socket: null
    };
    this.handleGamepadConnect = this.handleGamepadConnect.bind(this);
    this.handleGamepadDisconnect = this.handleGamepadDisconnect.bind(this);
    this.handleGamepadButtonChange = this.handleGamepadButtonChange.bind(this);
    this.handleGamepadAxisChange = this.handleGamepadAxisChange.bind(this);
  }

  handleGamepadConnect(gamepad) {
    this.props.updateControllerState({isControllerConnected: true})
    console.log(`Gamepad connected !`)
  }

  handleGamepadDisconnect() {
    this.props.updateControllerState({isControllerConnected: false})
    console.log(`Gamepad disconnected !`)
  }

  handleGamepadButtonChange(ev) {
    if(ev.button === "ARROW_UP") {
        this.state.socket.send(JSON.stringify({mode:"manual", gaitDirection: "forward"}))
    } else if(ev.button === "ARROW_DOWN") {
        this.state.socket.send(JSON.stringify({mode:"manual", gaitDirection: "backwards"}))
    } else {
      console.log("Unhandled event")
    }
  }

  handleGamepadAxisChange(ev) {
    console.log(ev)
  }

  componentDidMount() {
    
    this.setState({socket : new ReconnectingWebSocket("ws://192.168.4.1")}, () => {

      this.state.socket.onmessage = event => {
        
        let sensors = JSON.parse(event.data).sensors
        
        console.log(sensors)

        this.props.updateRobotState({sensors: {
          front: sensors[0],
          left: sensors[2],
          back: sensors[1],
          right: sensors[3],
        }})
 
      }

      this.state.socket.onopen = event => {
        this.props.updateConnectionState({isOpen: true})
      }
      this.state.socket.onclose = event => {
        this.props.updateConnectionState({isOpen: false})
      }
    })
  }

  render() {   
    const { modalIsOpen } = this.state;
    const { distances, isRobotOnline, isControllerConnected } = this.props;    
    return (
      <div data-tid="container">
        <Gamepad
            onConnect={this.handleGamepadConnect}
            onDisconnect={this.handleGamepadDisconnect}
            onButtonChange={this.handleGamepadButtonChange}
            onAxisChange={this.handleGamepadAxisChange}
            layout={Layouts.DUALSHOCK3}
          />
        <StyledWrapper>
          <Brand icon={logo} text="Quadpod robot" />
            <StyledCard>
              <Robot src={quadpod} alt=""/>
              <ProximityMeasurementLabel value={distances.right} top="220px" left="120px" />
              <ProximityMeasurementLabel value={distances.front} top="350px" left="120px" />
              <ProximityMeasurementLabel value={distances.left} top="350px" left="280px" />
              <ProximityMeasurementLabel value={distances.back} top="220px" left="280px" />
              <ControllerLabel src={controller} isVisible={isControllerConnected} />
              <ConnectivityLabel isOnline={isRobotOnline} />
            </StyledCard>
        </StyledWrapper>
      </div>
    );
  }
};

const mapStateToProps = state => ({
  distances: state.distances,
  isControllerConnected: state.isControllerConnected,
  isRobotOnline: state.isRobotOnline,
})

const mapDispatchToProps = dispatch => ({
  updateControllerState: state => dispatch(updateControllerState(state)),
  updateConnectionState: state => dispatch(updateConnectionState(state)),
  updateRobotState: state => dispatch(updateRobotState(state))
});

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(HomePage)
