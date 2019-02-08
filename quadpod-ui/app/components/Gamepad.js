import React from 'react'
import diff from 'deep-diff'

const DUALSHOCK3 = {
  axes: {
    '0':'LEFT_X',
    '1':'LEFT_Y',
    '2':'RIGHT_X',
    '3':'RIGHT_Y',
  },
  buttons: {
    '1': 'ARROW_UP',
    '0': 'ARROW_DOWN',
    '2': 'ARROW_LEFT',
    '16': 'ARROW_RIGHT',
  }
}

export const Layouts = { DUALSHOCK3 }

class Gamepad extends React.Component {
  constructor() {
    super()
    this.buttons = {}
    this.axes = {}
    this.state = {
      buttons: [],
      axes: []
    }
    this.pollGamepad = this.pollGamepad.bind(this)
    this.mapAxisEventToLayout = this.mapAxisEventToLayout.bind(this)
    this.mapButtonEventToLayout = this.mapButtonEventToLayout.bind(this)
  }

    mapButtonEventToLayout(ev){
      const { layout } = this.props
      return layout ? {...ev, button: layout.buttons[ev.button.toString()] } : ev
    }

    mapAxisEventToLayout(ev){
      const { layout } = this.props
      return ev
    }

    pollGamepad() {

      let gamepads = navigator.getGamepads ? navigator.getGamepads() : (navigator.webkitGetGamepads ? navigator.webkitGetGamepads() : [])
      let gamepad = gamepads[0]

      let buttons = gamepad.buttons.map(b => b.pressed)
      let buttonChanges = buttons.reduce((acc, el, idx) => {
        return el !== this.state.buttons[idx] ? acc.concat({button: idx, prev: this.state.buttons[idx], curr: el}) : acc
      }, [])

      let axes = gamepad.axes
      let axesChanges = axes.reduce((acc, el, idx) => {
        return el !== this.state.axes[idx] ? acc.concat({axis: idx, prev: this.state.axes[idx], curr: el}) : acc
      }, [])

      this.setState({buttons, axes})

      if (buttonChanges.length > 0) {
        for(let buttonChange of buttonChanges) {
          if (buttonChange.prev != undefined) {
            this.props.onButtonChange(this.mapButtonEventToLayout(buttonChange))
          }        
        }
      }

      if (axesChanges.length > 0) {
        for(let axisChange of axesChanges) {
          if (axisChange.prev != undefined) {
            this.props.onAxisChange(this.mapAxisEventToLayout(axisChange))
          }
        }
      }
  }

  componentDidMount() {
    
    window.addEventListener("gamepadconnected", e => {
      this.setState({
        interval: setInterval(this.pollGamepad, 100)
      })
      this.props.onConnect(e.gamepad)
    })

    window.addEventListener("gamepaddisconnected", e => {
      console.log('disconnected')
      clearInterval(this.state.interval)
      this.setState({
        interval: undefined
      })
      this.props.onDisconnect(e.gamepad)
    })
  }

  componentWillUnmount() {
    clearInterval(this.state.interval)
    this.setState({
      interval: undefined
    });
  }

  render() {
    return null
  }
}

export default Gamepad