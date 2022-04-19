##
# NickCoreUtils
#
# @version 0.1

install:
	@$(CC) brenfordsLaw.c -o /usr/bin/brenfordsLaw
	@$(CC) -lm cubic.c -o /usr/bin/cubic
	cp database.sh dmenu.sh saarlandCalculator.sh status.py /usr/bin



# end
