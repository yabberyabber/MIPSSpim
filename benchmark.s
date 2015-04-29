#  This is the countbits program, modified to be used as a benchmark
#  for the 315 lab projects.


# Here's some random test data:
# remnants from SPIM test:
#test1:	.word	0x0001004F	# test data : to count bits
#.text				# Begin body of code
#	.globl	main

# This test driver just loads a 32-bit word to get it's bits counted

main:	lui	$a0, 0x0001	# Load high 16 bits and clear low 16
	ori	$a0, $a0, 0x004F # low 16 bits, form 32-bit const.

	jal	countbits	# Go count the bits in $a0

#	can't use pseudoinstructions, because they're not implemented in this lab project!

	or	$t0, $zero, $v0	# save $v0 in $t0, dangit, because the HALT cmd wipes it out!
	ori	$v0, $zero, 10	# TRAP HALT; whose bright idea was it to pass codes
	syscall			# in the $v registers?

# countbits This function counts the number of '1' bits in a 32 bit word.
# It simply returns the number of 1's found.

# Count bits in $a0, returning $v0 as the count

# first, the "setup"

countbits:	and $v0, $zero, $zero	# Initialize counter in $v0

	ori	$t0, $zero, 1	# Initialize with a 32-bit mask with a '1' in the low bit of $t0

# now, the loop to count 1's:

loop:	and	$t1, $t0, $a0	# see if the bit is on
	beq	$t1, $zero, notset	# branch if bit was not set	
	addi	$v0, $v0, 1	# increment counter in $v0
notset:	sll	$t0, $t0, 1	# Shift the mask in register $t0 left one bit
	bne	$t0, $zero, loop  # Loop back if the mask in $t0 still has a bit
ret:	jr	$ra		# return to caller with count in $v0

	.end

