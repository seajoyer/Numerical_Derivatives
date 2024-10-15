{
  description = "Numerical Derivatives project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        pythonEnv = pkgs.python3.withPackages
          (ps: with ps; [ numpy matplotlib sympy ]);

        cppProject = pkgs.stdenv.mkDerivation {
          pname = "numerical_derivatives_example";
          version = "0.1.0";
          name = "numerical_derivatives-0.1.0";

          src = ./cpp;

          nativeBuildInputs = with pkgs; [ gnuplot cmake gnumake ];

          buildInputs = with pkgs; [ gnuplot boost catch2 ];

          cmakeFlags = [ "-DCMAKE_BUILD_TYPE=Release" ];

          buildPhase = ''
            cmake .
            ${pkgs.bash}/bin/bash
            make -j $NIX_BUILD_CORES
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp numerical_derivatives_example $out/bin/
          '';
        };

        pythonProject = pkgs.writeScriptBin "run-python" ''
          #!${pythonEnv}/bin/python
          import sys
          import os

          sys.path.insert(0, os.path.join(os.getcwd(), "py"))

          import demo
        '';

      in {
        packages = {
          cpp = cppProject;
          py = pythonProject;
          default = cppProject;
        };

        apps = {
          cpp = flake-utils.lib.mkApp { drv = cppProject; };
          py = flake-utils.lib.mkApp { drv = pythonProject; };
          default = self.apps.${system}.cpp;
        };

        devShells.default = pkgs.mkShell {
          name = "dev_shell";

          nativeBuildInputs = with pkgs; [
            cmake
            cmake-language-server
            gnumake
            gnuplot
            ccache
            git
            pyright
            pythonEnv
          ];

          buildInputs = with pkgs; [ boost catch2 ];
          shellHook = ''
            export CXXFLAGS="''${CXXFLAGS:-} -I${pkgs.catch2}/include -I${pkgs.gnuplot}/bin"

            export CCACHE_DIR=$HOME/.ccache
            export PATH="$HOME/.ccache/bin:$PATH"

            alias c=clear

            echo "======================================"
            echo "$(cmake   --version | head -n 1)"
            echo "$(g++     --version | head -n 1)"
            echo "$(make    --version | head -n 1)"
            echo "$(python  --version | head -n 1)"
            echo "$(gnuplot --version | head -n 1)"
            echo ""
            echo "Build the project:  nix build"
            echo "Run C++ project:    nix run .#cpp"
            echo "Run Python project: nix run .#py"
            echo ""
            echo "Happy coding!"
          '';
        };
      });
}
