##
# NickCoreUtils
#
# @version 0.1

install:
	chmod +x ./status.py
	@$(CC) brenfordsLaw.c -o /usr/bin/brenfordsLaw
	@$(CC) -lm cubic.c -o /usr/bin/cubic
	@$(CC) -lm quartic.c -o /usr/bin/quartic
	@$(cc) math/linearEquations.c -o /usr/bin/linearEquations
	cp database.sh dmenu.sh saarlandCalculator.sh status.py /usr/bin



# end
