# Array of tests to run (in order)
# Each test contains
#   description -
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.)
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in
# that they are not ran in isolation but in the order shown and the state of the device is not reset or
# altered in between executions (unless preconditions are used).
tests = [
	{
		"description": "PINA: 0x00 => PORTB: 0",
		"steps": [{"inputs": [("PINA", 0x00)], "iterations": 5}],
		"expected": [("PORTB", 0)],
	},
	{
		"description": "Press/release # (PA2), press/release Y(PA1) => PORTB: 1",
		"steps": [
			{"inputs": [("PINA", 0x04)], "iterations": 5},
			{"inputs": [("PINA", 0x00)], "iterations": 5},
			{"inputs": [("PINA", 0x02)], "iterations": 5},
			{"inputs": [("PINA", 0x00)], "iterations": 5},
		],
		"expected": [("PORTB", 1)],
	},
	{
		"description": "PINA7 locks the door",
		"steps": [{"inputs": [("PINA", 0x08)], "iterations": 5}],
		"expected": [("PORTB", 0)],
	},
	{
		"description": "Press # (PA2) then Y (PA1) immediately => PORTB: 0",
		"steps": [
			{"inputs": [("PINA", 0x04)], "iterations": 5},
			{"inputs": [("PINA", 0x02)], "iterations": 5},
		],
		"expected": [("PORTB", 0)],
	},
	{
		"description": "Press # and Y then release # then Y => PORTB: 0",
		"steps": [
			{"inputs": [("PINA", 0x06)], "iterations": 5},
			{"inputs": [("PINA", 0x02)], "iterations": 5},
			{"inputs": [("PINA", 0x00)], "iterations": 5},
		],
		"expected": [("PORTB", 0)],
	},
]

watch = ["SM1_STATE", "B", "A"]