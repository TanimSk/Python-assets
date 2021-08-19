if $barrel_nav.is_pressed():
			var rad = atan2(
				(event.position.y - 566),
				(event.position.x - 1425)
			)
			if event.position.x < (95 * cos(rad) + actuator_pos.x + 100) and \
			event.position.y < (95 * sin(rad) + actuator_pos.y):
				actuator.position = event.position

			rad = rad*180/PI
			print(rad)
			if abs(rad) < 90:
				print("right")
			else:
				print("left")
