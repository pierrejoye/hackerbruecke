<?php

mydump( null );
mydump( true );
mydump( 42 );
mydump( 42.42 );
mydump( "Forty two" );
mydump( array( 1, "2", "three" ) );
mydump( new stdClass );

mydump( fopen( __FILE__, "r" ) );
