package cz.muni.fi.pv021.TicTacToeBuilder;

/**
 *
 * @author Jakub Peschel
 */
public enum GamePlan {

    SIZE_11("GamePlan11x11.bmp"),
    SIZE_14("GamePlan14x14.bmp"),
    SIZE_20("GamePlan20x20.bmp");

    private final String text;

    private GamePlan(final String text) {
        this.text = text;
    }

    public String toString() {
        return text;
    }
}
