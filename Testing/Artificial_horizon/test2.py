def is_upside_down(roll):
    # Normalize roll to [0, 360)
    normalized_roll = roll % 360

    # Check if roll is between 90° and 270° (upside down)
    if 90 <= normalized_roll <= 270:
        return True
    return False

# Test cases
print(is_upside_down(-980))  # True (upside down)
