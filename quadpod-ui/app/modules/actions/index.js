export const CONTROLLER_STATE_UPDATE = 'CONTROLLER_STATE_UPDATE'
export const CONNECTION_STATE_UPDATE = 'CONNECTION_STATE_UPDATE'
export const ROBOT_STATE_UPDATE = 'ROBOT_STATE_UPDATE'


export const updateControllerState = state => ({
    type: CONTROLLER_STATE_UPDATE,
    state
})

export const updateConnectionState = state => ({
    type: CONNECTION_STATE_UPDATE,
    state
})

export const updateRobotState = state => ({
    type: ROBOT_STATE_UPDATE,
    state
})