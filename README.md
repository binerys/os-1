# os-1

Garima Lunawat: 004452540
Breanna Nery: 304454180

## Design Problem (1B)
Problem: Extend the shell to wait for individual subcommands, instead of waiting for them all to finish.

### Usage:
A user can either pass ``--wait`` to wait on all previous subcommands or ``--wait N``, where N is a specific subcommand. 

The subcommands are numbered similarly to file descriptors where the first subcommand is numbered as 0. 

###Constraints:
For the infinite waiting problem, we have assumed the user will utilize the ``--close N`` option to properly close pipes after calling ``--wait`` or ``--wait N``.

Furthermore, the user must handle dependencies. If a subcommand relies on a previous subcommand for input, the ``--wait N`` option must be called in the correct order. 

### Tests:
test-design.sh includes 3 test cases testing the design problem only. The program can be tested via ``make check``.
